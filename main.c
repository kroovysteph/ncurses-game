#include <ncurses.h>

const int HEIGHT = 24;
const int WIDTH = 68;



	char ch = 'a';
	int i = 1;


void gameLoop(void);
bool drawQuit(void);
void drawMap(int y, int x);






void drawMap(int y, int x) {



	return 0;
}


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
