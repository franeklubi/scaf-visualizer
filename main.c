#include <ncurses.h>


int main() {

    initscr();

    refresh();

    getch();

    endwin();


    return 0;
}
