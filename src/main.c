#include "rogue.h"

int main(void) {
	Player * user;
	int ch;
	srand(time(NULL));
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


Room ** mapSetUp() {

	Room ** rooms;
	rooms = malloc(sizeof(Room)*6);

	rooms[0] = createRoom(5, 5, 6, 8);
	drawRoom(rooms[0]);

	rooms[1] = createRoom(28, 5, 6, 8);
	drawRoom(rooms[1]);

	rooms[2] = createRoom(12, 19, 6, 12);
	drawRoom(rooms[2]);

	connectDoors(rooms[0]->doors[3], rooms[1]->doors[1]);
	connectDoors(rooms[2]->doors[0], rooms[1]->doors[2]);

	return rooms;
}



