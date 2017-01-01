#include "player.hpp"
#include "item.hpp"

//Add and remove items
void Player::addItem(const char* item) {
	Item* i = new Item;
	i->name = item;
	items.push_back(i);
}

const char* Player::removeItem(char* item) {
	const char* i;
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
		if (strcmp((*it)->name, item) == 0) {
			i = (*it)->name;
			delete *it;
			items.erase(it);
			return i;
		}
	}
	return NULL;
}

//Make a list of items in inventory
char* Player::listItems() {
	itemlist[0] = '\0';
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
		strcat(itemlist, (*it)->name);
		strcat(itemlist, ", ");
	}

	itemlist[strlen(itemlist)-2] = '\0';

	return itemlist;
}

//Get and set room
void Player::setRoom(Room* room) {
	location = room;
}

Room* Player::getRoom() {
	return location;
}


//Delete all items in inventory
void Player::deleteItems() {
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			delete *it;
	}
	items.clear();
}