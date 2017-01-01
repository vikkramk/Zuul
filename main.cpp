/*Zuul: A really simple text based maze game. The point is to get out.
* Use the items to mark where you've been
* LOOK OUT: There is also a trap
*/

#include <iostream>
#include <cstring>
#include <vector>
#include "player.hpp"
#include "room.hpp"

#define NUM_ROOMS 15
#define MAZE_WIDTH 3

void createMaze(Room* rooms[], const char* allitems[], const char* description, const char* directions[]);
void deleteMaze(Room** rooms);

int main() {
	Player player;
	Room* rooms[NUM_ROOMS];
	const char* description = "This is another room in the maze. It looks like the last. Go figure.";
	const char* allitems[] = {"bauble", "tablet", "lightbulb", "kitten", "book"};
	const char* directions[] = {"north", "south", "west", "east"};
	char input[80];
	bool finished = false;

	//Setup maze
	createMaze(rooms, allitems, description, directions);

	player.setRoom(rooms[0]);

	std::cout << "****Entering the Maze****" << std::endl;

	//Main loop: take input and run commands
	do {
		std::cout << "Enter Command:" << std::flush;
		std::cin >> input;
		if (strcmp(input, "go") == 0) {
			std::cin >> input;
			if (player.getRoom()->getExit(input) != NULL) {
				player.setRoom(player.getRoom()->getExit(input));
				std::cout << player.getRoom()->getDescription() << std::endl;
				std::cout << "Here there is: " << std::endl;
				std::cout << player.getRoom()->listItems() << std::endl;
				std::cout << "Exits are: " << std::endl;
				std::cout << player.getRoom()->listExits() << std::endl;
			}
			else
				std::cout << "There is no such exit from this room" << std::endl;
		}
		else if (strcmp(input, "list") == 0) {
			std::cout << "You have: " << player.listItems() << std::endl;
		}
		else if (strcmp(input, "look") == 0) {
			std::cout << player.getRoom()->getDescription() << std::endl;
			std::cout << "Here there is: " << std::endl;
			std::cout << player.getRoom()->listItems() << std::endl;
			std::cout << "Exits are: " << std::endl;
			std::cout << player.getRoom()->listExits() << std::endl;
		}
		else if (strcmp(input, "take") == 0) {
			const char* item;
			std::cin >> input;
			item = player.getRoom()->removeItem(input);
			if (item != NULL) {
				player.addItem(item);
				std::cout << "You have picked up the " << item << std::endl;
			}
			else {
				std::cout << "You see no such item here" << std::endl;
			}
		}
		else if (strcmp(input, "drop") == 0) {
			const char* item;
			std::cin >> input;
			item = player.removeItem(input);
			if (item != NULL) {
				player.getRoom()->addItem(item);
				std::cout << "You have dropped the " << item << std::endl;
			}
			else {
				std::cout << "You have no such item" << std::endl;
			}

		}
		else if (strcmp(input, "help") == 0) {
			std::cout << "Commands: go <exit>, list, look, take <item>, drop <item>, help, quit" << std::endl;
		}
		else if (strcmp(input, "quit") == 0) {
			finished = true;
		}
		else {
			std::cout << "-Invalid command-";
		}

		if (player.getRoom()->code == 14) {
			std::cout << "Wait! There's a trapdoor in the ceiling!" << std::endl;
			std::cout << "****Congrats! You have found the exit room!****" << std::endl;
			finished = true;
		}

		if (player.getRoom()->code == 7) {
			std::cout << "Wait! There's a trapdoor in the floor!" << std::endl;
			std::cout << "****You fall through and die. The end.****" << std::endl;
			finished = true;
		}

		std::cout << std::endl;
	} while (finished == false);

	deleteMaze(rooms);
	player.deleteItems();
}

//Create the maze, returns pointer to first room
void createMaze(Room* rooms[], const char* allitems[], const char* description, const char* directions[]) {
	//Make Rooms
	for (int i = 0; i < NUM_ROOMS; i++) {
		rooms[i] = new Room(description, i);
	}

	//Hint hint, it's a grid
	for (int i = 0; i < NUM_ROOMS; i++) {
		if (i<=NUM_ROOMS-MAZE_WIDTH)
			rooms[i]->setExit(directions[0], rooms[i+MAZE_WIDTH]);
		if (i>=MAZE_WIDTH)
			rooms[i]->setExit(directions[1], rooms[i-3]);
		if (i%MAZE_WIDTH!=0)
			rooms[i]->setExit(directions[2], rooms[i-1]);
		if (i%MAZE_WIDTH!=MAZE_WIDTH-1)
			rooms[i]->setExit(directions[3], rooms[i+1]);
	}

	//Put all items in first room
	rooms[0]->addItem(allitems[0]);
	rooms[0]->addItem(allitems[1]);
	rooms[0]->addItem(allitems[2]);
	rooms[0]->addItem(allitems[3]);
	rooms[0]->addItem(allitems[4]);
}

//Delete all of the rooms and their items
void deleteMaze(Room** rooms) {
	for (int i = 0; i < NUM_ROOMS; i++) {
		rooms[i]->deleteItems();
		delete rooms[i];
	}
}