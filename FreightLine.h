#pragma once
#include <iostream>
#include <vector>
#include "LeakedObjectDetector.h"

#include "FreightTrain.h"

struct FreightLine
{
    FreightTrain train1 = FreightTrain(4,20,"Fred");
    FreightTrain train2 = FreightTrain(2,25,"Bob");
    FreightTrain train3 = FreightTrain();

    FreightLine();
    ~FreightLine();

    bool dispatchTrain(const int trainNumber, const std::vector<int>& pickupDropoffList);
    bool dispatchTrain(FreightTrain& train, const std::vector<int>& pickupDropoffList);
    void describeTrain(const FreightTrain& train);
    JUCE_LEAK_DETECTOR(FreightLine)
};
