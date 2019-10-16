#include <ncurses.h>
#include <stdbool.h>

#include "./scaffolding/fileHandling.h"
#include "./scaffolding/Head.h"
#include "./scaffolding/helperFunctions.h"
#include "./scaffolding/interpreter.h"
#include "./scaffolding/Lines.h"


void drawLines() {

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
        drawLines();
        getch();
    }

    return 0;
}


int main() {
    initscr();

    refresh();

    // run("./test.scaf");

    getch();

    endwin();


    return 0;
}
