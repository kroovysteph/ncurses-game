#include <ncurses.h>
#include <stdlib.h>

const int HEIGHT = 24;
const int WIDTH = 68;

typedef struct Player {
	int xPosition;
	int yPosition;
	int health;
} Player;


//declare functions
int screenSetUp();
int mapSetUp();
Player * playerSetUp();


int main(void) {

	Player * user;
	int ch;
	screenSetUp();

	mapSetUp();
	user = playerSetUp();

	while (ch = getch() != 'q') {
		

	}

	endwin();

	return 0;
}




//seperate in another file later
int screenSetUp() {
	initscr();
	printw("Hello World!");
	noecho();
	refresh();
	return 0;
}


int mapSetUp() {

	mvprintw( 5, 5, "--------");
	mvprintw( 6, 5, "|......|");
	mvprintw( 7, 5, "|......|");
	mvprintw( 8, 5, "|......|");
	mvprintw( 9, 5, "|......|");
	mvprintw(10, 5, "--------");

	mvprintw( 5, 28, "--------");
	mvprintw( 6, 28, "|......|");
	mvprintw( 7, 28, "|......|");
	mvprintw( 8, 28, "|......|");
	mvprintw( 9, 28, "|......|");
	mvprintw(10, 28, "--------");

	mvprintw(19, 12, "------------");
	mvprintw(20, 12, "|..........|");
	mvprintw(21, 12, "|..........|");
	mvprintw(22, 12, "|..........|");
	mvprintw(23, 12, "|..........|");
	mvprintw(24, 12, "------------");

	return 0;
}



Player * playerSetUp() {
	Player * newPlayer;
	newPlayer = malloc(sizeof(Player));
	newPlayer->xPosition = 15;
	newPlayer->yPosition = 21;
	newPlayer->health = 20;

	mvprintw(newPlayer->yPosition, newPlayer->xPosition, "@");
	move(newPlayer->yPosition, newPlayer->xPosition);

	return newPlayer;
}













