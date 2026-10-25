//
// Created by P.C.V Saiteja on 23/10/26.
//

#include "../../include/character/Hero.h"
#include"../../include/inventory_items/Item.h"
#include <string>

int Hero::count = 0;

Hero::Hero( const std::string &name)
    :   name(name),
        experience(0),
        heroStats(40, 40, 6, 2, 1),
        heroBag(),
        equippedItem("Rusty Sword", "WEAPON", 3){
    heroBag += Item("Healing Potion", "POTION", 20);
    count++;
}

const Stats &Hero::getStats() const {
    return heroStats;
}

const Inventory &Hero::getBag() const {
    return heroBag;
}

std::string Hero::getName() const {
    return name;
}

int Hero::getExperience() const {
    return experience;
}

Hero& Hero::heal(int amount) {
    heroStats.heal(amount);
    return *this;
}

void Hero::takeDamage(int damage) {
    heroStats.takeDamage(damage);
}

bool Hero::isAlive() const {
    return heroStats.getHp() > 0;
}

Hero& Hero::pickUp(Item item) {
    if (heroBag.isFull()) {
        std::cerr << "Inventory is full" << std::endl;
        return *this;
    }

    heroBag += item;
    return *this;
}

Hero& Hero::gainXP(int amount) {
    if (amount <= 0) {
        std::cerr << "XP Must be greater than 0" << std::endl;
        return *this;
    }

    experience += amount;

    while (experience >= heroStats.getLevel() * 40) {
        experience -= heroStats.getLevel() * 40;
        ++heroStats;
    }
    return *this;
}

bool Hero::equip(int index) {
    if (index < 0 || index >= heroBag.getSize()) {
        std::cerr << "Equipment index out of bounds" << std::endl;
        return false;
    }

    const Item &item = heroBag[index];

    if (item.getType() != "WEAPON") {
        std::cerr << "Equipment type not supported" << std::endl;
        return false;
    }
    equippedItem = item;
    return true;
}

bool Hero::usePotion() {
    for (int i = 0; i < heroBag.getSize(); i++) {
        if (heroBag[i].getType() == "POTION") {
            heroStats.heal(heroBag[i].getPower());
            heroBag.removeAt(i);
            return true;
        }
    }

    std::cerr << "No potion found" << std::endl;
    return false;
}

int Hero::attackPower() const {
    return heroStats.getAttack() + equippedItem.getPower();
}

int Hero::heroCount() {
    return count;
}

std::ostream& operator<<(std::ostream& o, const Hero& hero) {
    o << "Hero: "<< hero.getName() << std::endl;
    o << "XP: " << hero.getExperience() << std::endl;
    o << hero.getStats();
    o << "Attack Power: " << hero.attackPower() << std::endl;
    o << "Equipped Weapon: " << hero.equippedItem << std::endl;
    o << "Inventory:\n" << hero.getBag();

    return o;
}

Hero::~Hero() {}