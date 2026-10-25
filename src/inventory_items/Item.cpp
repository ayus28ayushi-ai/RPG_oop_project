#include "../../include/inventory_items/Item.h"
using namespace std;

int Item::itemCount = 0;

// constructors and destructors
Item::~Item(){}
Item::Item(string name, string type, int power) {

    if (name != "") {
        itemName = name;
    } 
    else {
        cout << "Invalid name, using None" << endl;
        itemName = "None";
    }

    // validation for the type since it must be weapon or potion
    if (type == "weapon" || type == "potion") {
        itemType = type;
    } 
    else {
        cout << "Invalid type (use weapon or potion), using potion" << endl;
        itemType = "potion";
    }
 
    // power cannot be negative
    if (power >= 0) {
        itemPower = power;
    } 
    else {
        cout << "Invalid power (cannot be negative), using 0" << endl;
        itemPower = 0;
    }

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
    string name, type;
    int power;
    in >> name >> type >> power;
 
    if (!in) {
        return in;
    }
 
    // the type must be weapon or potion and the power cannot be negative
    if ((type != "weapon" && type != "potion") || power < 0) {
        cout << "Invalid item input" << endl;
        in.setstate(ios::failbit);
        return in;
    }
 
    // everything is valid, so the item is changed
    item.itemName = name;
    item.itemType = type;
    item.itemPower = power;
    return in;
}