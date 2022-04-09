#pragma once
#include <iostream>
#include <vector>
#include "LeakedObjectDetector.h"

#include "Wrappers.h"

struct FreightLine
{
    TrainWrapper train1 = TrainWrapper(new FreightTrain(4,20,"Fred"));
    TrainWrapper train2 = TrainWrapper(new FreightTrain(2,25,"Bob"));
    TrainWrapper train3 = TrainWrapper(new FreightTrain());
    //TrainWrapper train3(new FreightTrain()); // not sure I understand why I can't declare and initialize wrapper class member variables like this

    FreightLine();
    ~FreightLine();

    bool dispatchTrain(const int train, const std::vector<int>& pickupDropoffList);
    bool dispatchTrain(FreightTrain& train, const std::vector<int>& pickupDropoffList);
    void describeTrain(const FreightTrain& train);
    JUCE_LEAK_DETECTOR(FreightLine)
};
