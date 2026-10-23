#include "../../include/inventory_items/Item.h"
using namespace std;

int Item::itemCount = 0;

// constructors and destructors
Item::~Item(){}
Item::Item(string name, string type, int power) {
    itemName = name;
    itemType = type;
    itemPower = power;

    if (name != "None") {
        itemCount++;
    }
}

//getter functions 
string Item::getName() const { 
    return itemName; 
}
string Item::getType() const {
     return itemType; 
}
int Item::getPower() const {
     return itemPower; 
}
int Item::getTotalCreated() {
     return itemCount; 
}

//equality operator overloading function
bool Item::operator==(const Item& other) const {
    return itemName == other.itemName
        && itemType == other.itemType
        && itemPower == other.itemPower;
}

//output operator overloading function
ostream& operator<<(ostream& out, const Item& item) {
    out << item.itemName << " (" << item.itemType
        << ", power " << item.itemPower << ")";
    return out;
}

//input operator overloading function
istream& operator>>(istream& in, Item& item) {
    in >> item.itemName >> item.itemType >> item.itemPower;
    return in;
}