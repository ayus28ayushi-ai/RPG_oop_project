#include "Dungeon.h"
#include <stdexcept>
#include <string>
using namespace std;

Dungeon::Dungeon(int count) : rooms(nullptr), roomCount(count) {
    if (count < 1) {
        throw invalid_argument("A dungeon needs at least one room");
    }
    rooms = new Room[roomCount];
}

Dungeon::~Dungeon() {
    delete[] rooms;
}

int Dungeon::size() const { return roomCount; }

void Dungeon::checkRoom(int roomNumber) const {
    if (roomNumber < 0 || roomNumber >= roomCount) {
        throw out_of_range("Room number " + to_string(roomNumber) + " is out of range");
    }
}

Room& Dungeon::operator[](int roomNumber) {
    checkRoom(roomNumber);
    return rooms[roomNumber];
}

const Room& Dungeon::operator[](int roomNumber) const {
    checkRoom(roomNumber);
    return rooms[roomNumber];
}

// Loot rule used here: a room WITH a monster gives its loot when the monster dies (the monster
// carries it, and Game picks it up on the kill). Rooms 0 and 1 have no monster, so the room holds
// the loot and the player picks it up with menu option 7.
void Dungeon::buildDefault() {
    if (roomCount < 6) {
        throw logic_error("buildDefault needs at least 6 rooms");
    }

    rooms[0] = Room("Entrance Hall", "A torch lit hall with a heavy door behind you. A passage leads east.");
    rooms[0].setExit(EAST, 1);
    rooms[0].setLoot(Item("Healing Potion", "potion", 30));

    rooms[1] = Room("Armory", "Racks of rusted spears line the walls. Paths lead west, east and south.");
    rooms[1].setExit(WEST, 0).setExit(EAST, 2).setExit(SOUTH, 3);
    rooms[1].setLoot(Item("Iron Sword", "weapon", 4));

    rooms[2] = Room("Goblin Den", "Bones and stolen trinkets cover the floor. It smells terrible.");
    rooms[2].setExit(WEST, 1);
    rooms[2].setMonster(Monster("Goblin", 20, 5, 1, 30, Item("Healing Potion", "potion", 30)));

    rooms[3] = Room("Crypt", "Cold stone coffins line a damp chamber. Something rattles in the dark.");
    rooms[3].setExit(NORTH, 1).setExit(EAST, 4);
    rooms[3].setMonster(Monster("Skeleton", 30, 7, 2, 45, Item("Greater Potion", "potion", 40)));

    rooms[4] = Room("Orc Barracks", "Crude bunks and a smoking fire pit. Heavy footsteps echo here.");
    rooms[4].setExit(WEST, 3).setExit(EAST, 5);
    rooms[4].setMonster(Monster("Orc", 45, 9, 3, 70, Item("Greater Potion", "potion", 40)));

    rooms[5] = Room("Dragon's Lair", "A vast cavern glittering with gold. The air shimmers with heat.");
    rooms[5].setExit(WEST, 4);
    rooms[5].setMonster(Monster("Dragon", 60, 11, 5, 200, Item("Crown of the Realm", "weapon", 0)));
}
