#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

// Default constructor
Person::Person() : turn(0), currentFloor(0), targetFloor(0), angerLevel(0) {}

// Constructor that initializes a person based on a formatted string
Person::Person(string inputString) {
    int tempTurn = 0, tempCurrentFloor = 0, tempTargetFloor = 0, tempAngerLevel = 0;
    int i = 0;
    int num = 0;
    while (i < inputString.size() && inputString[i] != 'f') {
        num = num * 10 + (inputString[i] - '0');
        i++;
    }
    tempTurn = num;
    i++;
    num = 0;
    while (i < inputString.size() && inputString[i] != 't') {
        num = num * 10 + (inputString[i] - '0');
        i++;
    }
    tempCurrentFloor = num;
    i++;
    num = 0;
    while (i < inputString.size() && inputString[i] != 'a') {
        num = num * 10 + (inputString[i] - '0');
        i++;
    }
    tempTargetFloor = num;
    i++;
    num = 0;
    while (i < inputString.size()) {
        num = num * 10 + (inputString[i] - '0');
        i++;
    }
    tempAngerLevel = num;
    turn = tempTurn;
    currentFloor = tempCurrentFloor;
    targetFloor = tempTargetFloor;
    angerLevel = tempAngerLevel;
}

// Method to increase anger level based on the time
bool Person::tick(int currentTime) {
    if (currentTime % TICKS_PER_ANGER_INCREASE == 0) {
        angerLevel++;
        if (angerLevel >= MAX_ANGER) {
            angerLevel = MAX_ANGER;
            return true;  
        }
    }
    return false;  
}

// Method to print the person's details
void Person::print(ostream &outs) {    
    outs << "f" << currentFloor << "t" << targetFloor << "a" << angerLevel;
}

// Getter methods
int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {
    return currentFloor;
}

int Person::getTargetFloor() const {
    return targetFloor;
}

int Person::getAngerLevel() const {
    return angerLevel;
}
