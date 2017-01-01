/*Player class
* Has a location and items
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <cstring>
#include "room.hpp"
#include "item.hpp"

class Player {
	public:
		void addItem(const char* item);
		const char* removeItem(char* item);
		char* listItems();
		void setRoom(Room* room);
		Room* getRoom();
		void deleteItems();
	private:
		std::vector<Item*> items;
		char itemlist[80];
		Room* location;
};

#endif