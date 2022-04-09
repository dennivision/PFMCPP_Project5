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
    void pickupOrDropoffCars(const int numOfCars);
    void blowAirHorn(const float durationInSeconds);
    void proceedSomeStops(const unsigned long stops, const std::vector<int> pickupDropOffList);

    void printMessage(const std::string name) const;
    JUCE_LEAK_DETECTOR(FreightTrain)
};
