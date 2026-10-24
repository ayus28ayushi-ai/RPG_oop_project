#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include "Item.h"
#include "Stats.h"


class Monster {
private:
    std::string monsterName;
    Stats monsterStats;
    int rewardXp;
    Item monsterLoot;
    bool counted;              
    // makes sure one monster is counted as defeated only once
    static int defeatedCount;
public:
    Monster(const std::string& name = "Unknown", int hp = 1, int attack = 1,
            int defense = 0, int xpReward = 0, const Item& loot = Item());

    std::string name() const;
    const Stats& stats() const;
    int xpReward() const;
    const Item& loot() const;
    static int defeated();

    //Actions
    void takeDamage(int n);
    bool isAlive() const;
    void markDefeated();

    friend std::ostream& operator<<(std::ostream& out, const Monster& m);
};

#endif
