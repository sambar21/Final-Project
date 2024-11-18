/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    int explodedCount = 0;
    for (int i = 0; i < numPeople;) {
        if (people[i].tick(currentTime)) {
            for (int j = i; j < numPeople - 1; ++j) {
                people[j] = people[j + 1];
            }
            --numPeople;
            ++explodedCount;
        }
        else {
            ++i;
        }
    }
    return explodedCount;
}

void Floor::addPerson(Person newPerson, int request) {
    if (numPeople < MAX_PEOPLE_PER_FLOOR) {
        people[numPeople++] = newPerson;
        if (request > 0) {
            hasUpRequest = true;
        }
        else if (request < 0) {
            hasDownRequest = true;
        }
    }
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
   int sortedIndices[MAX_PEOPLE_PER_FLOOR];
   for (int i = 0; i < numPeopleToRemove; ++i) {
       sortedIndices[i] = indicesToRemove[i];
   }
   std::sort(sortedIndices, sortedIndices + numPeopleToRemove, std::greater<int>());
   for (int i = 0; i < numPeopleToRemove; ++i) {
       int index = sortedIndices[i];
       if (index >= 0 && index < numPeople) {
           for (int j = index; j < numPeople - 1; ++j) {
               people[j] = people[j + 1];
           }
           --numPeople;
       }
   }
   resetRequests();
}


void Floor::resetRequests() {
    hasUpRequest = false;
    hasDownRequest = false;
    
    for (int i = 0; i < numPeople; ++i) {
        int targetFloor = people[i].getTargetFloor();
        if (targetFloor > people[i].getCurrentFloor()) {
            hasUpRequest = true;
        }
        if (targetFloor < people[i].getCurrentFloor()) {
            hasDownRequest = true;
        }
        if (hasUpRequest && hasDownRequest) {
            break;
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
    string up = "U";
    outs << (hasUpRequest ? up : " ") << " ";
    for (int i = 0; i < numPeople; ++i){
        outs << people[i].getAngerLevel();
        outs << ((people[i].getAngerLevel() < MAX_ANGER) ? " " : " ");
    }
    outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
    string down = "D";
    outs << (hasDownRequest ? down : " ") << " ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "o ";
    }
    outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
    cout << endl;
    outs << "Select People to Load by Index" << endl;
    outs << "All people must be going in same direction!";
    /* O O
    // -|- -|-
    // | |
    // / \ / \ */
    outs << endl << " ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " O ";
    }
    outs << endl << " ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "-|- ";
    }
    outs << endl << " ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " | ";
    }
    outs << endl << " ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "/ \\ ";
    }
    outs << endl << "INDEX: ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << i << " ";
    }
    outs << endl << "ANGER: ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << people[i].getAngerLevel() << " ";
    }
    outs << endl << "TARGET FLOOR: ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << people[i].getTargetFloor() << " ";
    }
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
    return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
    return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}