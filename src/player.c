#include "rogue.h"

Player * playerSetUp() {
	Player * newPlayer;
	newPlayer = malloc(sizeof(Player));
	newPlayer->position.x = 15;
	newPlayer->position.y = 21;
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
			newY = user->position.y;
			newX = user->position.x - 1;
			break;
		//move down
		case 'j':
		case 'J':
			newY = user->position.y + 1;
			newX = user->position.x;
			break;
		//move up
		case 'k':
		case 'K':
			newY = user->position.y - 1;
			newX = user->position.x;
			break;
		//move right
		case 'l':
		case 'L':
			newY = user->position.y;
			newX = user->position.x + 1;
			break;
		default:
			break;
	}
	checkPosition(newY, newX, user);
	return 0;
}


//check what is at next position
int checkPosition(int newY, int newX, Player * user) {
	//int space;
	switch (mvinch(newY, newX)) {
		case '.':
		case '#':
		case '+':
			playerMove(newY, newX, user);
			break;
		default:
			move(user->position.y, user->position.x);
			break;
	}
	return 0;
}


int playerMove(int y, int x, Player * user) {

	mvprintw(user->position.y, user->position.x, ".");

	user->position.y = y;
	user->position.x = x;

	mvprintw(user->position.y, user->position.x, "@");
	move(user->position.y, user->position.x);

	return 0;
}
