//
// Created by P.C.V Saiteja on 23/10/26.
//

#ifndef OOPS_HERO_H
#define OOPS_HERO_H
#include <string>
#include "../inventory_items/Inventory.h"
#include "Stats.h"
#include "../inventory_items/Item.h"
#include <iostream>

class Hero {
private:
    std::string name;
    int experience;
    Stats heroStats;
    Inventory heroBag;
    Item equippedItem;

    static int count;
public:
    Hero (const std::string &name);
    ~Hero ();

    std::string getName () const;
    int getExperience() const;
    const Stats& getStats() const;
    const Inventory& getBag() const;

    Hero& pickUp(Item item);
    Hero& heal(int amount);
    Hero& gainXP(int amount);

    bool equip(int index);
    bool usePotion();
    int attackPower() const;
    void takeDamage(int damage);
    bool isAlive() const;

    static int heroCount();

    friend std::ostream& operator<< (std::ostream& o, const Hero& hero);
};

#endif //OOPS_HERO_H
