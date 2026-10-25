#ifndef DUNGEON_H
#define DUNGEON_H

#include "Room.h"

// the dungeon owns a dynamic array of Rooms and is never copied
class Dungeon {
private:
    Room* rooms;
    int roomCount;
    void checkRoom(int roomNumber) const;
public:
    explicit Dungeon(int count = 6);
    ~Dungeon();

    // copying is disabled: two Dungeons must never free the same array
    Dungeon(const Dungeon& other) = delete;
    Dungeon& operator=(const Dungeon& other) = delete;

    int size() const;
    Room& operator[](int roomNumber);               
    const Room& operator[](int roomNumber) const;

    // builds the six-room map from the blueprint (needs at least 6 rooms)
    void buildDefault();
};

#endif
