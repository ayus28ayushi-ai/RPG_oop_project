#include "../../include/world/Room.h"
using namespace std;


Room::Room(const string& name, const string& description)
    : roomName(name), roomDescription(description), roomMonster(), monsterPresent(false),
      roomLoot(), lootPresent(false) {
    for (int i = 0; i < DIRECTIONS; i++) {
        exits[i] = NO_EXIT;
    }
}

string Room::name() const { return roomName; }
string Room::description() const { return roomDescription; }

// a bad direction is ignored, and *this is returned to allow chaining
Room& Room::setExit(int direction, int roomNumber) {
    if (direction >= 0 && direction < DIRECTIONS) {
        exits[direction] = roomNumber;
    }
    return *this;
}

int Room::exit(int direction) const {
    if (direction < 0 || direction >= DIRECTIONS) {
        return NO_EXIT;
    }
    return exits[direction];
}

void Room::setMonster(const Monster& m) {
    roomMonster = m;
    monsterPresent = true;
}

Monster& Room::monster() { return roomMonster; }
const Monster& Room::monster() const { return roomMonster; }

bool Room::hasLiveMonster() const { return monsterPresent && roomMonster.isAlive(); }

void Room::setLoot(const Item& item) {
    roomLoot = item;
    lootPresent = true;
}

bool Room::hasLoot() const { return lootPresent; }

// the loot can be taken only once
Item Room::takeLoot() {
    if (!lootPresent) {
        return Item();
    }
    lootPresent = false;
    return roomLoot;
}

ostream& operator<<(ostream& out, const Room& r) {
    const char* dirNames[DIRECTIONS] = {"North", "East", "South", "West"};
    out << "=== " << r.roomName << " ===" << endl;
    out << r.roomDescription << endl;
    out << "Exits:";
    bool any = false;
    for (int i = 0; i < DIRECTIONS; i++) {
        if (r.exits[i] != NO_EXIT) {
            out << " " << dirNames[i] << "(" << r.exits[i] << ")";
            any = true;
        }
    }
    if (!any) {
        out << " none";
    }
    out << endl;
    if (r.hasLiveMonster()) {
        out << "Monster: " << r.roomMonster << endl;
    }
    else if (r.monsterPresent) {
        out << "The remains of the " << r.roomMonster.name() << " lie here." << endl;
    }
    if (r.lootPresent) {
        out << "Loot: " << r.roomLoot << endl;
    }
    return out;
}
