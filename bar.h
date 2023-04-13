// bar.h
// ****************************************************************************
//
// Project: Animated Bar Chart
// Author: Shahryar Ahmed
//
// ****************************************************************************
//
// The Bar class creates an object of a single bar, using name, value, and
// category. This class also implements the overloaded comparison operators.
//
// ****************************************************************************

#include <iostream>
#include <string>
#include "myrandom.h" // used in graders, do not remove
using namespace std;

//
// Bar
//
class Bar {
 private:
    // Private member variables for a Bar object
    // NOTE: You should not be allocating memory on the heap for this class.
    string name;
    int value;
    string category;

 public:

    // default constructor:
    Bar() {
        name = "";
        value = 0;
        category = "";
        
    }

    //
    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    //
    Bar(string name, int value, string category) {
        this->name = name;
        this->value = value;
        this->category = category;
    }

    // destructor:
    virtual ~Bar() {
        
    }

    // getName:
	string getName() {
        return name;
	}

    // getValue:
	int getValue() {
        return value;
	}

    // getCategory:
	string getCategory() {
        return category;
	}

	// operators
	bool operator<(const Bar &other) const {
        return this->value < other.value;
	}

	bool operator<=(const Bar &other) const {
        return this->value <= other.value;
	}

	bool operator>(const Bar &other) const {
        return this->value > other.value;
	}

	bool operator>=(const Bar &other) const {
        return this->value >= other.value; 
	}
};

