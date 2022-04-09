#pragma once
#include <iostream>
#include <iomanip>

#include "LeakedObjectDetector.h"

struct AquariumTank
{
    float waterCapacity, pHLevel, currentWaterLevel, evaporationRate;
    int fishLivingIn;

    struct Fish;

    AquariumTank();
    AquariumTank(float capacity);
    ~AquariumTank();

    void addFish(Fish fish, int quantity);
    void addWater(float amountOfWater);
    void adjustPH(float phAdjustment);

    void ageTank(int days);
    void init(float capacity);
    JUCE_LEAK_DETECTOR(AquariumTank)
};

struct AquariumTank::Fish
    {
        std::string name, breed;
        float maxSalinity, age, maxAge;
        
        Fish();
        ~Fish();

        bool canLiveInThisWater(float waterPH, float waterSalinity);
        void ageFish(float amountOfTime);
        bool isStillAlive(float waterPH, float waterSalinity);
    };
