#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "./scaffolding/fileHandling.h"
#include "./scaffolding/Head.h"
#include "./scaffolding/helperFunctions.h"
#include "./scaffolding/interpreter.h"
#include "./scaffolding/Lines.h"


void drawLines(ProgramState* state) {
    for ( uint32_t x = 0; x < state->buffer_ptr->no_lines; x++ ) {
        mvprintw(
            x, 0,
            "[%x](%x):\t\"",
            x, state->buffer_ptr->lines_len[x]
        );

        for ( uint32_t i = 0; i < state->buffer_ptr->lines_len[x]; i++ ) {
            printw(
                "%c",
                state->buffer_ptr->lines[x][i]
            );
        }
        printw("\"");

        // mvchgat(0, x, 1, A_REVERSE, 0, NULL);
        // mvchgat(0, 7, 1, A_REVERSE, 0, NULL);
    }
    refresh();
}


int run(char* filename) {
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
        drawLines(&state);
        char c = getch();
        if ( c == 'q' ) {
            return 0;
        }

        state.r_head_ptr->pos_x++;
    }

    return 0;
}


int main() {
    initscr();

    noecho();

    curs_set(false);

    run("./test.scaf");

    endwin();


    return 0;
}
