#include "../../include/world/Dungeon.h"
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

    
    rooms[0] = Room("Mahadwar, the Grand Gateway",
        "You stand beneath a towering sandstone gateway carved with lotus petals and marching elephants. "
        "Oil lamps flicker in the niches, and the scent of camphor drifts from a passage leading east.");
    rooms[0].setExit(EAST, 1);
    rooms[0].setLoot(Item("Sanjivani Elixir", "POTION", 30));

    rooms[1] = Room("Shastragar, the Forgotten Armoury",
        "Dusty racks of talwars, spears and dented shields line the walls, each blade etched with a half-erased prayer. "
        "A cracked war drum hangs from a pillar. Paths lead west, east and south.");
    rooms[1].setExit(WEST, 0).setExit(EAST, 2).setExit(SOUTH, 3);
    rooms[1].setLoot(Item("Iron Khanda", "WEAPON", 4));

    rooms[2] = Room("Pishacha Gufa, the Flesh-Eater's Cave",
        "Smoke hangs thick over heaps of stolen temple bells, snapped bangles and gnawed bones. "
        "The air reeks of rotting offerings, and hungry red eyes glint from the dark.");
    rooms[2].setExit(WEST, 1);
    rooms[2].setMonster(Monster("Pishacha", 20, 5, 1, 30, Item("Sanjivani Elixir", "POTION", 30)));

    rooms[3] = Room("Shmashan Ghat, the Cremation Ground",
        "A silent riverbank under a pale moon. Ash drifts on a cold wind, half-burnt pyres smoulder, "
        "and something hangs upside down from an old banyan tree, whispering your name.");
    rooms[3].setExit(NORTH, 1).setExit(EAST, 4);
    rooms[3].setMonster(Monster("Vetala", 30, 7, 2, 45, Item("Amrit Kalash", "POTION", 40)));

    rooms[4] = Room("Rakshasa Chhavni, the Demon Fortress",
        "A fortress of blood-red sandstone, its courtyard littered with iron clubs and half-eaten feasts. "
        "Great fire pits roar, and the ground trembles under the heavy tread of a Rakshasa.");
    rooms[4].setExit(WEST, 3).setExit(EAST, 5);
    rooms[4].setMonster(Monster("Rakshasa", 45, 9, 3, 70, Item("Amrit Kalash", "POTION", 40)));

    rooms[5] = Room("Vritra's Lair",
        "A vast cavern glittering with gold and rubies, where the serpent-dragon Vritra lies coiled around a "
        "river of molten light. The heat is unbearable, and the Swarna Mukut gleams on the highest heap of treasure.");
    rooms[5].setExit(WEST, 4);
    rooms[5].setMonster(Monster("Vritra", 60, 11, 5, 200, Item("Swarna Mukut", "WEAPON", 0)));
}
