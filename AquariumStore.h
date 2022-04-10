#pragma once
#include <iostream>
#include "LeakedObjectDetector.h"

#include "AquariumTank.h"

struct AquariumStore
{
    AquariumTank freshWaterTank1 {120.f};//= TankWrapper(new AquariumTank(120.f));
    AquariumTank freshWaterTank2 {55.f};//= TankWrapper(new AquariumTank(55.f));
    AquariumTank freshWaterTank3 {25.f};//= TankWrapper(new AquariumTank(25.f));
    AquariumTank saltWaterTank {180.f};//= TankWrapper(new AquariumTank(180.f));
    AquariumStore();
    ~AquariumStore();

    void topOffTanks();
    void ageTanks(const int weeks);
    JUCE_LEAK_DETECTOR(AquariumStore)
};
