#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "./scaffolding/fileHandling.h"
#include "./scaffolding/Head.h"
#include "./scaffolding/helperFunctions.h"
#include "./scaffolding/interpreter.h"
#include "./scaffolding/Lines.h"


#define BLUE    1
#define RED     2


void drawHead(Head* head, uint32_t x_mod, uint8_t colour) {
    mvchgat(
        head->pos_y, head->pos_x+x_mod,
        1, A_STANDOUT, colour, NULL
    );
}


void drawLines(WINDOW* win, ProgramState* state) {
    clear();

    for ( uint32_t y = 0; y < state->buffer_ptr->no_lines; y++ ) {
        mvprintw(
            y, 0,
            "(%x):\t\"",
            state->buffer_ptr->lines_len[y]
        );

        // getting current cursor position for head drawing mod
        int cur_y, cur_x;
        getyx(win, cur_y, cur_x);

        for ( uint32_t x = 0; x < state->buffer_ptr->lines_len[y]; x++ ) {
            printw(
                "%c",
                state->buffer_ptr->lines[y][x]
            );
        }
        printw("\"");

        if ( state->w_head_ptr->pos_y == y ) {
            drawHead(state->w_head_ptr, cur_x, RED);
        }
        if ( state->r_head_ptr->pos_y == y ) {
            drawHead(state->r_head_ptr, cur_x, BLUE);
        }
    }


    refresh();
}


int run(WINDOW* win, char* filename) {
    Head r_head = genHead();
    Head w_head = genHead();
    w_head.destructive = true;

    FILE* file = fopen(filename, "r");
        uint32_t file_size = getSize(file);
        char* start_ptr = loadFile(file, file_size);
    fclose(file);

    Lines* lines_buffer = dissectLines(start_ptr, file_size);
    free(start_ptr);
    if ( !lines_buffer ) {
        fprintf(stderr, "Error with creating lines_buffer\n");
        return 1;
    }

    ProgramState state = genProgramState(lines_buffer, &r_head, &w_head);

    bool should_end = false;

    while ( !should_end ) {
        should_end = execute(&state);
        drawLines(win, &state);
        char c = getch();
        if ( c == 'q' ) {
            return 0;
        }

        state.r_head_ptr->pos_x++;
    }

    return 0;
}


int main(int argc, char** argv) {
    WINDOW* win = initscr();

    start_color();
    if ( has_colors() != FALSE ) {
        init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
        init_pair(RED, COLOR_RED, COLOR_BLACK);
    }

    noecho();

    curs_set(FALSE);


    Flags o = {0, 0, 0, ""};

    if ( argc < 2 ) {
        endwin();
        fprintf(stderr, "No input files\n");
        return 0;
    }

    for ( int x = 1; x < argc; x++ ) {
        if ( verifyPath(argv[x], &o) ) {
            run(win, argv[x]);
        } else {
            endwin();
            fprintf(stderr, "Can't open path \"%s\"\n", argv[x]);
            return 0;
        }
    }

    endwin();


    return 0;
}
