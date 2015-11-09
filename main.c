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
int handleInput(int input, Player * user);
int playerMove(int y, int x, Player * user);
int checkPosition(int newY, int newX, Player * user);

Player * playerSetUp();


int main(void) {

	Player * user;
	int ch;
	screenSetUp();

	mapSetUp();
	user = playerSetUp();

	//main game loop
	while ((ch = getch()) != 'q') {
		handleInput(ch, user);

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
	return 1;
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

	playerMove(21, 15, newPlayer);

	return newPlayer;
}


int handleInput(int input, Player * user) {

	int newY;
	int newX;
	switch (input) {

		//move left
		case 'h':
		case 'H':
			newY = user->yPosition;
			newX = user->xPosition - 1;
			break;

		//move down
		case 'j':
		case 'J':
			newY = user->yPosition + 1;
			newX = user->xPosition;
			break;

		//move up
		case 'k':
		case 'K':
			newY = user->yPosition - 1;
			newX = user->xPosition;
			break;

		//move right
		case 'l':
		case 'L':
			newY = user->yPosition;
			newX = user->xPosition + 1;
			break;

		default:
			break;

	}

	checkPosition(newY, newX, user);

	return 0;
}

//check what is at next position
int checkPosition(int newY, int newX, Player * user) {

	int space;
	switch (mvinch(newY, newX)) {

		case '.':
			playerMove(newY, newX, user);
			break;
		default:
			move(user->yPosition, user->xPosition);
			break;

	}

	return 0;
}



int playerMove(int y, int x, Player * user) {

	mvprintw(user->yPosition, user->xPosition, ".");

	user->yPosition = y;
	user->xPosition = x;

	mvprintw(user->yPosition, user->xPosition, "@");
	move(user->yPosition, user->xPosition);

	return 0;
}







