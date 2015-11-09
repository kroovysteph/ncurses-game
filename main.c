#include <ncurses.h>


	char ch = 'a';
	int i = 1;


void gameLoop(void);
bool drawQuit(void);









int main(void) {

	initscr();
	cbreak();
	noecho();

	while (true) {
		ch = getch();

		if (ch == 'q') {
			if (true) {      //true durch drawQuit() ersetzen
				break;
			}
		}


		mvaddch(i,i, ch);
		i++;
	}

	endwin();

	return 0;
}
