#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include "Item.h"

class Inventory {
private:
    // member variables
    Item* items;
    int capacity;
    int count;
    
public:
    // constructors and destructors
    Inventory(int cap = 10);
    Inventory(const Inventory& other);
    ~Inventory();
    
    // getters and bool functions
    int getSize() const;
    bool isFull() const;
    bool removeAt(int position);

    //operator overloading functions
    Inventory& operator=(const Inventory& other);
    Inventory& operator+=(const Item& item);
    Item& operator[](int position);
    const Item& operator[](int position) const;
    bool operator==(const Inventory& other) const;
    bool operator!=(const Inventory& other) const;
    friend std::istream& operator>>(std::istream& in, Inventory& bag);
    friend std::ostream& operator<<(std::ostream& out, const Inventory& bag);

};

#endif