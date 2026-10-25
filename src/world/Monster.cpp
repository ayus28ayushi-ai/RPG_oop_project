#include "../../include/world/Monster.h"
using namespace std;

int Monster::defeatedCount = 0;

// values that make no sense are corrected
Monster::Monster(const string& name, int hp, int attack, int defense, int xpReward, const Item& loot)
    : monsterName(name == "" ? "Unknown" : name),
      monsterStats(hp < 1 ? 1 : hp, hp < 1 ? 1 : hp, attack < 0 ? 0 : attack, defense < 0 ? 0 : defense, 1),
      rewardXp(xpReward < 0 ? 0 : xpReward),
      monsterLoot(loot),
      counted(false) {}


string Monster::name() const { return monsterName; }
const Stats& Monster::stats() const { return monsterStats; }
int Monster::xpReward() const { return rewardXp; }
const Item& Monster::loot() const { return monsterLoot; }
int Monster::defeated() { return defeatedCount; }

// damage is passed to Stats, which stops HP at 0
void Monster::takeDamage(int n) {
    if (n > 0) {
        monsterStats.takeDamage(n);
    }
}

bool Monster::isAlive() const { return monsterStats.getHp() > 0; }

// counts the monster once, and only when it is really dead
void Monster::markDefeated() {
    if (!isAlive() && !counted) {
        counted = true;
        defeatedCount++;
    }
}

ostream& operator<<(ostream& out, const Monster& m) {
    out << m.monsterName << " [" << m.monsterStats << "] XP reward " << m.rewardXp;
    if (!m.isAlive()) {
        out << " (defeated)";
    }
    else {
        out << ", drops " << m.monsterLoot;
    }
    return out;
}
