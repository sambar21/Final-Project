/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    if (commandString == "S") {
        isSave = true;
    }
    else if (commandString == "Q") {
        isQuit = true;
    }
    else if (commandString[0] == 'e') {
        elevatorId = commandString[1] - '0';
        if (commandString[2] == 'f') {
            targetFloor = commandString[3] - '0';
        }
        else if (commandString[2] == 'p') {
            isPickup = true;
        }
    }
    else if (commandString == "P") {
        isPass = true;
    }

    
}


bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if (isPass || isQuit || isSave) {
        return true;
    }
    if (elevatorId < 0 || elevatorId >= NUM_ELEVATORS) {
        return false;
    }
    const Elevator& elevator = elevators[elevatorId];
    if (elevator.isServicing()) {
        return false;
    }
    if (!isPickup) {
        if (targetFloor < 0 || targetFloor >= NUM_FLOORS) {
            return false;
        }
        if (targetFloor == elevator.getCurrentFloor()) {
            return false;
        }
    }
    return true;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    targetFloor = currentFloor;

    for (char indexChar : pickupList) {
        int index = indexChar - '0';

        if (index < 0 || index >= MAX_PEOPLE_PER_FLOOR) {
            cout << "Invalid index: " << index << endl; 
            continue;  
        }

        peopleToPickup[numPeopleToPickup++] = index;
        const Person& person = pickupFloor.getPersonByIndex(index);
        int angerLevel = person.getAngerLevel();
        int personTargetFloor = person.getTargetFloor();
        totalSatisfaction += (MAX_ANGER - angerLevel);

        if (abs(personTargetFloor - currentFloor) > abs(targetFloor - currentFloor)) {
            targetFloor = personTargetFloor;
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
return isPass;
}

bool Move::isSaveMove() const {
return isSave;
}

bool Move::isQuitMove() const {
return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}