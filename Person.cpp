/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Person.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

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

void Person::print(ostream &outs) {    
    outs << "f" << currentFloor << "t" << targetFloor << "a" << angerLevel;
}
