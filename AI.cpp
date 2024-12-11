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
    int selectedElevator = -1;
    int targetRequestFloor = -1;
    int shortestDistance = NUM_FLOORS + 1;
    
    // check for angry passengers 
    for (int floorIndex = 0; floorIndex < NUM_FLOORS; ++floorIndex) {
        if (buildingState.floors[floorIndex].hasUpRequest || 
            buildingState.floors[floorIndex].hasDownRequest) {
            // check anger levels on  floor
            for (int p = 0; p < buildingState.floors[floorIndex].numPeople; ++p) {
                if (buildingState.floors[floorIndex].people[p].angerLevel >= 8) {
                    // find closest available elevator
                    for (int e = 0; e < NUM_ELEVATORS; ++e) {
                        if (!buildingState.elevators[e].isServicing) {
                            int distance = abs(buildingState.elevators[e].currentFloor - floorIndex);
                            if (distance < shortestDistance) {
                                selectedElevator = e;
                                targetRequestFloor = floorIndex;
                                shortestDistance = distance;
                            }
                        }
                    }
                }
            }
        }
    }

    // If no urgent cases, handle normal requests
    if (selectedElevator == -1) {
        for (int e = 0; e < NUM_ELEVATORS; ++e) {
            if (!buildingState.elevators[e].isServicing) {
                for (int f = 0; f < NUM_FLOORS; ++f) {
                    if (buildingState.floors[f].hasUpRequest || 
                        buildingState.floors[f].hasDownRequest) {
                        int distance = abs(buildingState.elevators[e].currentFloor - f);
                        if (distance < shortestDistance) {
                            selectedElevator = e;
                            targetRequestFloor = f;
                            shortestDistance = distance;
                        }
                    }
                }
            }
        }
    }

    if (selectedElevator != -1 && targetRequestFloor != -1) {
        if (buildingState.elevators[selectedElevator].currentFloor == targetRequestFloor) {
            return "e" + to_string(selectedElevator) + "p";
        } else {
            return "e" + to_string(selectedElevator) + "f" + to_string(targetRequestFloor);
        }
    }

    return "";
}



string getAIPickupList(const Move& move, const BuildingState& buildingState,
                      const Floor& floorToPickup) {
    string pickupList = "";
    int currentFloor = floorToPickup.getPersonByIndex(0).getCurrentFloor();
    bool goingUp = false;
    
    //  determine direction based on angriest passenger
    int maxAnger = -1;
    for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
        Person p = floorToPickup.getPersonByIndex(i);
        if (p.getAngerLevel() > maxAnger) {
            maxAnger = p.getAngerLevel();
            goingUp = p.getTargetFloor() > currentFloor;
        }
    }
    
    // pick up passengers going in the same direction
    for (int i = 0; i < floorToPickup.getNumPeople(); ++i) {
        Person p = floorToPickup.getPersonByIndex(i);
        bool personGoingUp = p.getTargetFloor() > currentFloor;
        if (personGoingUp == goingUp) {
            pickupList += to_string(i);
        }
    }
    
    return pickupList;
}

