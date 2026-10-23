#include "../../include/inventory_items/Inventory.h"
using namespace std;

// constructor 
Inventory::Inventory(int cap) {
    // validating the cappacity
    if (cap >= 1 && cap <= 100) {
        capacity = cap;
    } else {
        cout << "Invalid capacity (use 1 to 100), using 10" << endl;
        capacity = 10;
    }
    count = 0;
    items = new Item[capacity];
}

// copy constructor
Inventory::Inventory(const Inventory& other) {
    capacity = other.capacity;
    count = other.count;
    items = new Item[capacity];
    for (int i = 0; i < count; i++) {
        items[i] = other.items[i];
    }
}

// destructor
Inventory::~Inventory() {
    delete[] items;
}

// getters and bool functions
int Inventory::getSize() const {
    return count;
}

bool Inventory::isFull() const {
    return count == capacity;
}

// removes the item at the position and moves further right items to left
bool Inventory::removeAt(int position) {
    // checking the bounds
    if (position < 0 || position >= count) {
        return false;
    }
    for (int i = position; i < count - 1; i++) {
        items[i] = items[i + 1];
    }
    count--;
    return true;
}

// assignment operator overloading function
Inventory& Inventory::operator=(const Inventory& other) {
    if (this != &other) {
        delete[] items;
        capacity = other.capacity;
        count = other.count;
        items = new Item[capacity];
        for (int i = 0; i < count; i++) {
            items[i] = other.items[i];
        }
    }
    return *this;
}

// add operator overloading function  
Inventory& Inventory::operator+=(const Item& item) {
    // checking for empty item
    if (item.getName() == "None") {
        cout << "Cannot add an empty item" << endl;
    } else if (count == capacity) {
        cout << "Inventory full!" << endl; // checking for saturated inventory capacity
    } else {
        items[count] = item;
        count++;
    }
    return *this;
}

// subscript operator overloading function  
Item& Inventory::operator[](int position) {
    // checking the bounds
    if (position < 0 || position >= count) {
        cout << "Position " << position << " is out of range" << endl;
        abort();
    }
    return items[position];
}

// subscript operator overloading function (read only)
const Item& Inventory::operator[](int position) const {
    // checking the bounds
    if (position < 0 || position >= count) {
        cout << "Position " << position << " is out of range" << endl;
        abort();
    }
    return items[position];
}

// equality operator overloading function
bool Inventory::operator==(const Inventory& other) const {
    // validating the size
    if (count != other.count) {
        return false;
    }
    for (int i = 0; i < count; i++) {
        if (!(items[i] == other.items[i])) {
            return false;
        }
    }
    return true;
}

// inequality operator overloading function
bool Inventory::operator!=(const Inventory& other) const {
    return !(*this == other);
}

// input operator overloading function (a number, then that many items)
istream& operator>>(istream& in, Inventory& bag) {
    int howMany;
    in >> howMany;
 
    if (!in) {
        return in;
    }
    // checking for invalid negative number of items
    if (howMany < 0) {
        cout << "Invalid number of items" << endl;
        return in;
    }
 
    // validating for the bag to have enough free space
    if (howMany > bag.capacity - bag.count) {
        cout << "Not enough space in the bag for " << howMany << " items" << endl;
        return in;
    }
 
    for (int i = 0; i < howMany; i++) {
        Item item;
        in >> item;
        
        if (!in) {
            return in;
        }
        bag += item;
    }
    return in;
}

// output operator overloading function
ostream& operator<<(ostream& out, const Inventory& bag) {
    out << "Inventory (" << bag.count << "/" << bag.capacity << ")" << endl;
    if (bag.count == 0) {
        out << "  Bag is empty" << endl;
    } else {
        for (int i = 0; i < bag.count; i++) {
            out << "  [" << i << "] " << bag.items[i] << endl;
        }
    }
    return out;
}