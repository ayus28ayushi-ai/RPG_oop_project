#ifndef GAME_H
#define GAME_H
#include "../standins/Hero.h"
#include "../standins/Dungeon.h"
#include "../standins/Monster.h"
#include "../standins/Room.h"
#include "../standins/Item.h"      // ← note the 's'
#include "../standins/Stats.h"
#include "../standins/Inventory.h"

class Game{

    private:
        Hero hero_;
        Dungeon dungeon_;
        int currentRoom_;
        int previousRoom_;
        int turnCount_;
    
    public:
        Game();
        void run();
};

#endif