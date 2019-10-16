#include <ncurses.h>
#include <stdio.h>

#include "./scaffolding/fileHandling.h"
#include "helperFunctions.h"

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
            return 1;
        }
    }

    endwin();


    return 0;
}
