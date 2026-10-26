# ⚔️ RealmForge: A Console Fantasy RPG in C++

A modular, text-based fantasy RPG developed in C++17. The project demonstrates core Object-Oriented Programming (OOP) principles — encapsulation, dynamic memory management, operator overloading, composition, dynamic array allocation, static members, and function pointers — inside a zero-dependency console game 

---

##  Gameplay Overview

Explore a 6-room dungeon layout starting from the **Entrance Hall** to **Vritra's Lair**. Collect loot, manage your dynamic inventory, level up stats, and battle enemies in round-based combat to retrieve the *Crown of the Realm*.

### World Map Layout
```text
[0: Entrance Hall] --- [1: Armory] --------- [2: Goblin Den]
                           |
                     [3: Crypt] --- [4: Orc Barracks] --- [5: Vritra's Lair]
```


### Key Mechanics
* **Dynamic Stats & Levelling:** Base stats scale automatically using custom overloads (`++`) as XP thresholds (`level × 40 XP`) are met.
* **Turn-Based Combat:** Round-based menu allowing attacks (20% critical chance via function pointers), potion usage, or fleeing (50% success rate).
* **Inventory & Gear Management:** Custom dynamic container handling item addition (`+=`), item indexing (`[]`), stream output (`<<`), and safe deep-copy transfers.

---

##  Architecture & OOP Concept Mapping

The system comprises 8 modular, co-operating classes engineered around clean encapsulation and high cohesion:

| Class | Primary Responsibility | OOP Concepts Demonstrated |
| :--- | :--- | :--- |
| **`Item`** | Represents weapons/potions with power scaling | Encapsulation, static counters, overloaded `==`, `<<` |
| **`Inventory`** | Dynamic heap-allocated backpack container| Dynamic memory (`new[]`/`delete[]`), Rule of Three (Copy Constructor, Copy Assignment Operator, Destructor), `+=`, `[]`, `==`, `!=`, `<<` |
| **`Stats`** | Encapsulates HP, max HP, attack, defense, level | Prefix/postfix `++` (level up), `+=`, `==`, `<<` |
| **`Hero`** | Player entity managing stats, inventory, equipped gear | Composition (*has-a*), method chaining using `this` pointer, const correctness |
| **`Monster`** | Enemy entity with distinct stats, XP, and drop tables| Static metrics tracking, const pointers, composition |
| **`Room`** | Dungeon node with up to 4 exits, monsters, and loot| Method chaining (`*this`), composition |
| **`Dungeon`** | Manages room array and map layout | Dynamic allocation|
| **`Game`** | Main engine running the menu loop and combat pipelin | Seed-based random generation |

---

##  Project Structure

```text
.
├── include/
│   ├── character/
│   │   ├── Hero.h
│   │   └── Stats.h
│   ├── engine/
│   │   └── Game.h
│   ├── inventory_items/
│   │   ├── Inventory.h
│   │   └── Item.h
│   └── world/
│       ├── Dungeon.h
│       ├── Monster.h
│       └── Room.h
├── src/
│   ├── character/
│   │   ├── Hero.cpp
│   │   └── Stats.cpp
│   ├── engine/
│   │   └── Game.cpp
│   ├── inventory_items/
│   │   ├── Inventory.cpp
│   │   └── Item.cpp
│   └── world/
│       ├── Dungeon.cpp
│       ├── Monster.cpp
│       └── Room.cpp
├── main.cpp
├── README.md
```


---

##  Building & Running

### Prerequisites
* Any C++17 compatible compiler
### Compilation

Using standard `g++`:
```bash
g++ src/main.cpp src/character/*.cpp src/engine/*.cpp src/inventory_items/*.cpp src/world/*.cpp
```

### Execution
```bash
./a
```
---
Enjoy playing !


