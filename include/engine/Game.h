#ifndef GAME_H
#define GAME_H
#include "../character/Hero.h"
#include "../world/Dungeon.h"

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