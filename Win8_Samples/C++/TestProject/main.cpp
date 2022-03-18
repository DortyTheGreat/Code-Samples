#include <ncurses.h>

int main() {
    initscr();

    printw("Typical symbol \'A\': ");
    addch('A');

    printw("\nUnderline and bold symbol \'A\': ");


    printw("\nPress any key...");
    getch();
    endwin();
    return 0;
}
