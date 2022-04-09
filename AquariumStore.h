#pragma once
#include <iostream>
#include "LeakedObjectDetector.h"

#include "Wrappers.h"

struct AquariumStore
{
    TankWrapper freshWaterTank1 = TankWrapper(new AquariumTank(120.f));
    TankWrapper freshWaterTank2 = TankWrapper(new AquariumTank(55.f));
    TankWrapper freshWaterTank3 = TankWrapper(new AquariumTank(25.f));
    TankWrapper saltWaterTank = TankWrapper(new AquariumTank(180.f));
    AquariumStore();
    ~AquariumStore();

    void topOffTanks() const;
    void ageTanks(const int weeks) const;
    JUCE_LEAK_DETECTOR(AquariumStore)
};
