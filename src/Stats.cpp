//
// Created by P.C.V Saiteja on 23/10/26.
//

#include "../include/Stats.h"
#include <iostream>

Stats::Stats(int hp, int maxHp, int attack, int defence, int level)
    : hp(hp), maxHp(maxHp), attack(attack),
      defence(defence), level(level) {
    if (maxHp <= 0 || hp < 0 || hp > maxHp ||
        attack < 0 || defence < 0 || level < 1) {
        std::cerr << "Invalid arguments\n";
        // Avoid leaving an invalid object.
        this->hp = 100;
        this->maxHp = 100;
        this->attack = 5;
        this->defence = 2;
        this->level = 1;
        }
}

int Stats::getHp() const {
    return hp;
}

int Stats::getMaxHp() const {
    return maxHp;
}

int Stats::getAttack() const {
    return attack;
}

int Stats::getDefence() const {
    return defence;
}

int Stats::getLevel() const {
    return level;
}

void Stats::takeDamage(int damage) {
    if (damage < 0 ) {
        std::cerr << "Invalid arguments\n" << std::endl;
        return;
    }
    hp -= damage;

    if (hp < 0) hp = 0;
}

void Stats::heal(int amount) {
    if (amount <= 0) {
        std::cerr << "Invalid arguments\n" << std::endl;
        return;
    }

        hp += amount;


    if (hp > maxHp) hp = maxHp;
}

Stats& Stats::operator++() {
    level++;
    maxHp += 10;
    attack += 2;
    defence += 1;
    hp = maxHp;

    return *this;
}

Stats& Stats::operator+=(const StatBonus& bonus) {
    maxHp += bonus.maxHp;
    attack += bonus.attack;
    defence += bonus.defence;
    
    return *this;
}

bool Stats::operator==(const Stats& other) const {
    return hp == other.getHp() && maxHp == other.getMaxHp() &&
        attack == other.getAttack() && defence == other.getDefence() &&
            level == other.getLevel();
}

Stats Stats::operator++(int) {
    Stats old = *this;
    ++(*this);
    return old;
}

std::ostream& operator<<(std::ostream& o, const Stats& stats) {
    o << "Level: " << stats.getLevel() << std::endl;
    o << "HP: " << stats.getHp() << "/" << stats.getMaxHp() << std::endl;
    o << "Attack: " << stats.getAttack();
    o << "Defence: " << stats.getDefence();

    return o;
}