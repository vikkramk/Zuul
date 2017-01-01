/*Room class
* Holds items and has a map for exits
*/

#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>
#include <map>
#include <cstring>
#include "item.hpp"

struct cmp_str
{
   bool operator()(const char *a, const char *b) const
   {
      return strcmp(a, b) < 0;
   }
};

class Room {
	public:
		Room(const char* description, int code);
		void setDescription(const char* description);
		const char* getDescription();
		void addItem(const char* item);
		const char* removeItem(char* item);
		char* listItems();
		void setExit(const char* name, Room* room);
		Room* getExit(char* exit);
		char* listExits();
		void deleteItems();
		int code;

	private:
		const char* description;
		std::vector<Item*> contents;
		std::map<const char*, Room*, cmp_str> exits;
		char itemlist[80];
		char exitlist[80];
};


#endif