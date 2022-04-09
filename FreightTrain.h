#pragma once
#include <iostream>
#include <vector>
//#include <iomanip>
#include "LeakedObjectDetector.h"

struct FreightTrain
{
    int numberOfLocomotives = 1;
    int numberOfFreightCars = 1;
    float maxCargoWeight { numberOfLocomotives * 8000.f };
    float grossCargoWeight { numberOfFreightCars * 110.f };
    std::string conductorName = "conductor";

    FreightTrain();
    FreightTrain(int locomotives, int cars, std::string conductor);
    ~FreightTrain();

    void proceedToNextStop();
    void pickupOrDropoffCars(int numOfCars);
    void blowAirHorn(float durationInSeconds);
    void proceedSomeStops(unsigned long stops, std::vector<int> pickupDropOffList);

    void printMessage(std::string name);
    JUCE_LEAK_DETECTOR(FreightTrain)
};
