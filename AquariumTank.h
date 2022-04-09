#pragma once
#include <iostream>
#include <iomanip>

#include "LeakedObjectDetector.h"

struct AquariumTank
{
    float waterCapacity{0.f}, pHLevel{0.f}, currentWaterLevel{0.f}, evaporationRate{0.f};
    int fishLivingIn{0};

    struct Fish;

    AquariumTank();
    AquariumTank(const float capacity);
    ~AquariumTank();

    void addFish(const Fish fish, const int quantity);
    void addWater(const float amountOfWater);
    void adjustPH(const float phAdjustment);

    void ageTank(const int days);
    void init(const float capacity);
    JUCE_LEAK_DETECTOR(AquariumTank)
};

struct AquariumTank::Fish
    {
        std::string name, breed;
        float maxSalinity, age, maxAge;
        
        Fish();
        ~Fish();

        bool canLiveInThisWater(const float waterPH, const float waterSalinity) const;
        void ageFish(const float amountOfTime);
        bool isStillAlive(const float waterPH, const float waterSalinity) const;
    };
