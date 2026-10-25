//
// Created by P.C.V Saiteja on 23/10/26.
//

#ifndef OOPS_STATS_H
#define OOPS_STATS_H

#include <iostream>

struct StatBonus;

class Stats {
private:
    int hp;
    int maxHp;
    int attack;
    int defence;
    int level;

public:
    // Default and parameterised constructor
    Stats(int hp = 100, int maxHp = 100, int attack = 5, int defence = 2, int level = 1);
    int getHp() const;
    int getMaxHp() const;
    int getAttack() const;
    int getDefence() const;
    int getLevel() const;
    void takeDamage(int damage);
    void heal(int amount);

    // Operator overloading
    // Prefix and postfix increment
    Stats& operator++();
    Stats operator++(int);

    // To apply stat Bonus
    Stats& operator+=(const StatBonus& bonus);

    // To compare two stats objects
    bool operator==(const Stats& other) const;

    // Displaying stats
    friend std::ostream& operator<<(std::ostream& o, const Stats& stats);

};

struct StatBonus {
    int maxHp;
    int attack;
    int defence;
};
#endif //OOPS_STATS_H
