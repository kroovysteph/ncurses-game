#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Position {
	int x;
	int y;
	//TILE_TYPE tile;
} Position;

typedef struct Room {
	Position position;    //top-left corner of the room
	int height;
	int width;
	Position ** doors;
	//Monster ** monsters;
	//Item ** items;
} Room;

typedef struct Player {
	Position position;
	int health;
	//Room * room;
} Player;

//declare functions
int screenSetUp();
Room ** mapSetUp();
int handleInput(int input, Player * user);
int playerMove(int y, int x, Player * user);
int checkPosition(int newY, int newX, Player * user);

//room functions
Room * createRoom(int x, int y, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * doorOne, Position * doorTwo);


Player * playerSetUp();

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

	//mvprintw( 5, 5, "--------");
	//mvprintw( 6, 5, "|......|");
	//mvprintw( 7, 5, "|......|");
	//mvprintw( 8, 5, "|......|");
	//mvprintw( 9, 5, "|......|");
	//mvprintw(10, 5, "--------");

	rooms[0] = createRoom(5, 5, 6, 8);
	drawRoom(rooms[0]);

	//mvprintw( 5, 28, "--------");
	//mvprintw( 6, 28, "|......|");
	//mvprintw( 7, 28, "|......|");
	//mvprintw( 8, 28, "|......|");
	//mvprintw( 9, 28, "|......|");
	//mvprintw(10, 28, "--------");

	rooms[1] = createRoom(28, 5, 6, 8);
	drawRoom(rooms[1]);

	//mvprintw(19, 12, "------------");
	//mvprintw(20, 12, "|..........|");
	//mvprintw(21, 12, "|..........|");
	//mvprintw(22, 12, "|..........|");
	//mvprintw(23, 12, "|..........|");
	//mvprintw(24, 12, "------------");

	rooms[2] = createRoom(12, 19, 6, 12);
	drawRoom(rooms[2]);

	connectDoors(rooms[0]->doors[3], rooms[1]->doors[1]);

	return rooms;
}



Room * createRoom(int x, int y, int height, int width) {

	Room * newRoom;
	newRoom = malloc(sizeof(Room));

	newRoom->position.x = x;
	newRoom->position.y = y;
	newRoom->height = height;
	newRoom->width = width;


	newRoom->doors = malloc(sizeof(Position) * 4);


	//top door
	newRoom->doors[0] = malloc(sizeof(Position));
	newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1;
	newRoom->doors[0]->y = newRoom->position.y;

	//left door
	newRoom->doors[1] = malloc(sizeof(Position));
	newRoom->doors[1]->y = rand() % (height - 2) + newRoom->position.y + 1;
	newRoom->doors[1]->x = newRoom->position.x;

	//bottom door
	newRoom->doors[2] = malloc(sizeof(Position));
	newRoom->doors[2]->x = rand() % (width - 2) + newRoom->position.x + 1;
	newRoom->doors[2]->y = newRoom->position.y + newRoom->height - 1;

	//right door
	newRoom->doors[3] = malloc(sizeof(Position));
	newRoom->doors[3]->y = rand() % (height - 2) + newRoom->position.y + 1;
	newRoom->doors[3]->x = newRoom->position.x + width - 1;

	return newRoom;
}


int drawRoom(Room * room) {

	int x;
	int y;

	//draw top and bottom
	for (x = room->position.x; x < room->position.x + room->width; x++) {
		mvprintw(room->position.y, x, "-"); //top
		mvprintw(room->position.y + room->height - 1, x, "-"); //bottom
	}

	//draw floors and side walls
	for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
		//draw side walls
		mvprintw(y, room->position.x, "|");
		mvprintw(y, room->position.x + room->width - 1, "|");
		//draw floors
		for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
			mvprintw(y, x, ".");
		}
	}

	//draw doors - Chapter 06 - min07:47
	mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
	mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
	mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
	mvprintw(room->doors[3]->y, room->doors[3]->x, "+");

	return 1;
}



int connectDoors(Position * doorOne, Position * doorTwo) {

	Position temp;
	temp.x = doorOne->x;
	temp.y = doorOne->y;

	while (1) {
		//step left
		if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x - 1) == ' ')) {
			mvprintw(temp.y, temp.x - 1, "#");
			temp.x = temp.x - 1;

		//step right
		} else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x + 1) == ' ')) {
			mvprintw(temp.y, temp.x + 1, "#");
			temp.x = temp.x + 1;

		//step down
		} else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y + 1, temp.x) == ' ')) {
			mvprintw(temp.y + 1, temp.x, "#");
			temp.y = temp.y + 1;

		//step up
		} else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y - 1, temp.x) == ' ')) {
			mvprintw(temp.y - 1, temp.x, "#");
			temp.y = temp.y - 1;
		} else {
			return 0;
		}

		getch();
}

	return 1;
}



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







