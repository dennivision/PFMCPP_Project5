#include "AquariumStore.h"

AquariumStore::AquariumStore()
{
    std::cout << "An AquariumStore was created" << std::endl;
}

AquariumStore::~AquariumStore()
{
    std::cout << "An AquariumStore was destroyed" << std::endl;
}

void AquariumStore::topOffTanks()
{
    while(freshWaterTank1.currentWaterLevel < 1.f)  { freshWaterTank1.addWater(5.f); }
    while(freshWaterTank2.currentWaterLevel < 1.f)  { freshWaterTank2.addWater(5.f); }
    while(freshWaterTank3.currentWaterLevel < 1.f)  { freshWaterTank3.addWater(5.f); }
    while(saltWaterTank.currentWaterLevel < 1.f)    { saltWaterTank.addWater(5.f); }
}

void AquariumStore::ageTanks(const int weeks)
{
    if (weeks > 0)
    {
        freshWaterTank1.ageTank(weeks * 7);
        freshWaterTank2.ageTank(weeks * 7);
        freshWaterTank3.ageTank(weeks * 7);
        saltWaterTank.ageTank(weeks * 7);
    }
}
