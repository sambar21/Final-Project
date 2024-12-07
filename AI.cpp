/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <Varun Sambatur, John Butler, Daniel Joseph, Miguel Truschel>
 * <>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState) {
    int selectedElevator = -1; // tracks elevator chosen to service request
    int targetRequestFloor = -1; // target floor
    int shortestDistance = NUM_FLOORS + 1; // shortest distance to floor

    for (int elevatorIndex = 0; elevatorIndex < NUM_ELEVATORS; ++elevatorIndex) {
        // loop through each elevator skipping elevators servicing a request
        if (buildingState.elevators[elevatorIndex].isServicing) {
            continue;
        }

        // looping through all floors, based on whether its going up or down find the distance and go if closer request is found
        for (int floorIndex = 0; floorIndex < NUM_FLOORS; ++floorIndex) {
            if (buildingState.floors[floorIndex].hasUpRequest || buildingState.floors[floorIndex].hasDownRequest) {
                int distanceToFloor = abs(buildingState.elevators[elevatorIndex].currentFloor - floorIndex);
                if (distanceToFloor < shortestDistance) {
                    selectedElevator = elevatorIndex;
                    targetRequestFloor = floorIndex;
                    shortestDistance = distanceToFloor;
                }
            }
        }
    }

    // if selected elevator is found and target request floor is found
    if (selectedElevator != -1 && targetRequestFloor != -1) {
        if (buildingState.elevators[selectedElevator].currentFloor == targetRequestFloor) {
            return "e" + to_string(selectedElevator) + "p"; // return "eX p" where X is elevator id
        } else {
            return "e" + to_string(selectedElevator) + "f" + to_string(targetRequestFloor); // return "eX fY" where X is elevator id and Y is target floor to travel to
        }
    }

    return ""; // Pass if no requests are pending
}


string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
    // Prioritize lower anger levels if possible while picking up people 
    
    string pickupIndicesList = "";
    bool pickupDirectionUp = false;
    
    // loop through all people on the floor and check if they are going up or down
    for (int personIndex = 0; personIndex < floorToPickup.getNumPeople(); ++personIndex) {
        Person currentPerson = floorToPickup.getPersonByIndex(personIndex);
        if (currentPerson.getTargetFloor() > currentPerson.getCurrentFloor()) {
            pickupDirectionUp = true;
            break;
        }
        if (currentPerson.getTargetFloor() < currentPerson.getCurrentFloor()) {
            pickupDirectionUp = false;
            break;
        }
        // if person target floor is equal to current floor, then they are on the same floor
        // if person target floor is greater than current floor, then they are going up
        // if person target floor is less than current floor, then they are going down
        // pickupDirectionUp is a metric to demonstrate this 
    }
    // loop through again
    // if direction matches pickupDirectionUp, then add person to pickup list
    // making sure to append to the pickup list
    for (int personIndex = 0; personIndex < floorToPickup.getNumPeople(); ++personIndex) {
        Person currentPerson = floorToPickup.getPersonByIndex(personIndex);
        bool currentPersonGoingUp = currentPerson.getTargetFloor() > currentPerson.getCurrentFloor();
        
        if (currentPersonGoingUp == pickupDirectionUp) {
            pickupIndicesList += to_string(personIndex);
        }
    }
    
    return pickupIndicesList;
}
