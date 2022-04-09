#include "AquariumTank.h"

void AquariumTank::init(float capacity)
{
    waterCapacity = capacity;
    pHLevel = 7.f;
    currentWaterLevel = 0.8f;
    evaporationRate = 0.25f;
    fishLivingIn = 0;
}

AquariumTank::AquariumTank()
{
    init(15.f);
    std::cout << "an AquariumTank was created" << std::endl; 
}

AquariumTank::AquariumTank(float capacity)
{
    init(capacity);
    std::cout << "a " << std::fixed << waterCapacity << "G AquariumTank was created" << std::endl; 
}

AquariumTank::~AquariumTank()
{
    std::cout << "a " << std::fixed << waterCapacity << "G AquariumTank with " << fishLivingIn << " fish living in it was destroyed" << std::endl; 
}

void AquariumTank::addFish(AquariumTank::Fish fish, int quantity)
{
    if( fish.canLiveInThisWater(pHLevel, 0.f) )
    {
        std::cout << "AquariumTank::addFish() addding " << quantity << " fish" << std::endl; 
        fishLivingIn += quantity;
    }
    else
    {
        std::cout << "AquariumTank::addFish() just killed " << quantity << " fish" << std::endl; 
    }
}

void AquariumTank::addWater(float amountOfWater)
{
    float currentWaterAmount = waterCapacity * currentWaterLevel;
    std::cout   << "AquariumTank::addWater() trying to add " << std::fixed << amountOfWater << " gallons of water to a "
                << waterCapacity << " gallon tank"
                << " that's filled to " << std::fixed << (100 * currentWaterLevel) << "% of its capacity" << std::endl; 
    currentWaterAmount += amountOfWater;
    if(currentWaterAmount > waterCapacity)
    {
        std::cout << "AquariumTank::addWater() just spilled " << std::defaultfloat << currentWaterAmount - waterCapacity << " gallons!" << std::endl; 
        currentWaterAmount = waterCapacity;
    }

    currentWaterLevel = currentWaterAmount / waterCapacity;
    std::cout   << "AquariumTank::addWater() new water level: " << std::fixed << (100 * currentWaterLevel)
                << "% of " <<  waterCapacity << " gallons" << std::endl; 
}

void AquariumTank::adjustPH(float phAdjustment)
{
    pHLevel += phAdjustment;
    if(pHLevel > 14.f)
        pHLevel = 14.f;

    if(pHLevel < 0.f)
        pHLevel = 0.f;

    std::cout << "AquariumTank::adjustPH() new pH level: " << pHLevel << std::endl; 
}

void AquariumTank::ageTank(int days)
{
    float currentWaterAmount = waterCapacity * currentWaterLevel;
    float waterEvaporated = 0;
    int i = 0;
    bool exitFlag = false;
    while (i < days)
    {
        ++i;
        waterEvaporated += evaporationRate;
        currentWaterAmount -= evaporationRate;
        if ( currentWaterAmount <= 0.f)
        {
            exitFlag = true;
            currentWaterAmount = 0.f;
        }
        currentWaterLevel = currentWaterAmount / waterCapacity;
        std::cout << "AquariumTank::ageTank() day " << std::defaultfloat << i << " water level: " << std::setprecision(4) << std::fixed << (100 * currentWaterLevel) << "%" << std::endl; 
        if (exitFlag)
        {
            std::cout << "AquariumTank::ageTank() managed to kill " << std::defaultfloat << fishLivingIn << " fish " << std::endl;
            fishLivingIn = 0;
            break;
        }
    }
    std::cout << "AquariumTank::ageTank() after " << std::defaultfloat << i << " days a total of " << std::setprecision(2) << waterEvaporated << " gallons of water evaporated" << std::endl; 
}

AquariumTank::Fish::Fish() : name("new fish"), breed("betta"), maxSalinity(0.75f), age(0.f), maxAge(3.f)
{ 
    std::cout << "AquariumTank::Fish '" <<  name << "' was created" << std::endl;
    std::cout << "    it is a '" <<  breed << "'" <<std::endl;
    std::cout << "    and can live in water with a salinity level of up to " << maxSalinity << std::endl;
    std::cout << std::endl;
}

AquariumTank::Fish::~Fish()
{
    std::cout << "AquariumTank::Fish '" << name << "' needs to be flushed" << std::endl;
}

bool AquariumTank::Fish::canLiveInThisWater(float waterPH, float waterSalinity)
{
    if((waterPH >= 6.f && waterPH <= 8.f) && (waterSalinity < maxSalinity))
    {
        std::cout << "a fish named '" <<  name << "' can live in water with a pH of " << waterPH << " and a salintiy of " << waterSalinity << std::endl;
        return true;
    }
    std::cout << "a fish named '" <<  name << "' can NOT live in water with a pH of " << waterPH << " and a salintiy of " << waterSalinity << std::endl;
    return false;
}

void AquariumTank::Fish::ageFish(float amountOfTime)
{ 
    age += amountOfTime;
    std::cout << "AquariumTank::Fish " <<  name << " is this old: " << age << std::endl;
}

bool AquariumTank::Fish::isStillAlive(float waterPH, float waterSalinity)
{
    return (canLiveInThisWater(waterPH, waterSalinity) && (age < maxAge));
}
