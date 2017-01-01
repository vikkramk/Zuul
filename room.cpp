#include "room.hpp"
#include "item.hpp"

//Copy description and code
Room::Room(const char* description, int code) {
	this->description = description;
	this->code = code;
}

//Setters and getters
void Room::setDescription(const char* description) {
	this->description = description;
}

const char* Room::getDescription() {
	return description;
}

void Room::addItem(const char* item) {
	Item* i = new Item;
	i->name = item;
	contents.push_back(i);
}

const char* Room::removeItem(char* item) {
	const char* i;
	for (std::vector<Item*>::iterator it = contents.begin(); it != contents.end(); it++) {
		if (strcmp((*it)->name, item) == 0) {
			i = (*it)->name;
			delete *it;
			contents.erase(it);
			return i;
		}
	}
	return NULL;
}

void Room::setExit(const char* name, Room* room) {
	exits[name] = room;
}

Room* Room::getExit(char* name) {
	if (exits.count(name)) {
		return exits[name];
	}
	return NULL;
}

//Make a list of items in room
char* Room::listItems() {
	itemlist[0] = '\0';
	for (std::vector<Item*>::iterator it = contents.begin(); it != contents.end(); it++) {
		strcat(itemlist, (*it)->name);
		strcat(itemlist, ", ");
	}

	itemlist[strlen(itemlist)-2] = '\0';

	return itemlist;
}

//Make a list of exits from room
char* Room::listExits() {
	exitlist[0] = '\0';
	for (std::map<const char*, Room*>::iterator it=exits.begin(); it!=exits.end(); it++) {
		strcat(exitlist, it->first);
		strcat(exitlist, ", ");
	}
	exitlist[strlen(exitlist)-2] = '\0';

	return exitlist;
}

//Delete all items in room
void Room::deleteItems() {
	for (std::vector<Item*>::iterator it = contents.begin(); it != contents.end(); it++) {
			delete *it;
	}
	contents.clear();
}