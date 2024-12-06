/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState) {
    // Strategy overview:
    // 1. If an elevator is idle and there's a floor with a request, service that floor
    // 2. If no requests, pass
    
    for (int i = 0; i < NUM_ELEVATORS; ++i) {
        // If this elevator is not servicing a request
        if (!buildingState.elevators[i].isServicing) {
            // Look for floors with up or down requests
            for (int j = 0; j < NUM_FLOORS; ++j) {
                if (buildingState.floors[j].hasUpRequest || 
                    buildingState.floors[j].hasDownRequest) {
                    
                    // If elevator not already on this floor, service it
                    if (buildingState.elevators[i].currentFloor != j) {
                        return "e" + to_string(i) + "f" + to_string(j);
                    }
                    // If on this floor, do a pickup
                    else {
                        return "e" + to_string(i) + "p";
                    }
                }
            }
        }
    }
    
    // If no elevators can service a request, pass
    return "";
}


string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {
    // Strategy: 
    // 1. Pickup all people on the floor going in the same direction
    // 2. Prioritize lower anger levels if possible
    
    string pickupList = "";
    bool isGoingUp = false;
    
    // Determine direction of pickup
    for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
        Person person = floorToPickup.getPersonByIndex(i);
        if (person.getTargetFloor() > person.getCurrentFloor()) {
            isGoingUp = true;
            break;
        }
        if (person.getTargetFloor() < person.getCurrentFloor()) {
            isGoingUp = false;
            break;
        }
    }
    
    // Select people going in the correct direction
    for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
        Person person = floorToPickup.getPersonByIndex(i);
        bool personGoingUp = person.getTargetFloor() > person.getCurrentFloor();
        
        if (personGoingUp == isGoingUp) {
            pickupList += to_string(i);
        }
    }
    
    return pickupList;
}