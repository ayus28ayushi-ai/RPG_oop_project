#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

class Item {
private:
    // member variables
    std::string itemName;
    std::string itemType;
    int itemPower;
    static int itemCount;
public:
    // constructors and destructors
    Item(std::string name = "None", std::string type = "potion", int power = 0);
    ~Item();

    // getters
    std::string getName() const;
    std::string getType() const;
    int getPower() const;
    static int getTotalCreated();

    // overloading functions
    friend std::ostream& operator<<(std::ostream& out, const Item& item);
    friend std::istream& operator>>(std::istream& in, Item& item);
    bool operator==(const Item& other) const;

};

#endif