#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include "Item.h"
#include "Monster.h"


const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;
const int DIRECTIONS = 4;
const int NO_EXIT = -1;


class Room {
private:
    std::string roomName;
    std::string roomDescription;
    Monster roomMonster;
    bool monsterPresent;
    Item roomLoot;
    bool lootPresent;
    int exits[DIRECTIONS];
public:

    Room(const std::string& name = "Empty Room", const std::string& description = "");

    std::string name() const;
    std::string description() const;

    // exits
    Room& setExit(int direction, int roomNumber);   // returns *this so calls can be chained
    int exit(int direction) const;                  // -1 when there is no exit or a bad direction

    // monster
    void setMonster(const Monster& m);
    Monster& monster();                             
    const Monster& monster() const;
    bool hasLiveMonster() const;

    // loot
    void setLoot(const Item& item);
    bool hasLoot() const;
    Item takeLoot();                               

    friend std::ostream& operator<<(std::ostream& out, const Room& r);
};

#endif
