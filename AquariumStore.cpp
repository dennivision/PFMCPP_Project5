#include "AquariumStore.h"

AquariumStore::AquariumStore()
{
    std::cout << "An AquariumStore was created" << std::endl;
}

AquariumStore::~AquariumStore()
{
    std::cout << "An AquariumStore was destroyed" << std::endl;
}

void AquariumStore::topOffTanks() const
{
    while(freshWaterTank1.tankPtr->currentWaterLevel < 1.f)  { freshWaterTank1.tankPtr->addWater(5.f); }
    while(freshWaterTank2.tankPtr->currentWaterLevel < 1.f)  { freshWaterTank2.tankPtr->addWater(5.f); }
    while(freshWaterTank3.tankPtr->currentWaterLevel < 1.f)  { freshWaterTank3.tankPtr->addWater(5.f); }
    while(saltWaterTank.tankPtr->currentWaterLevel < 1.f)    { saltWaterTank.tankPtr->addWater(5.f); }
}

void AquariumStore::ageTanks(const int weeks) const
{
    if (weeks > 0)
    {
        freshWaterTank1.tankPtr->ageTank(weeks * 7);
        freshWaterTank2.tankPtr->ageTank(weeks * 7);
        freshWaterTank3.tankPtr->ageTank(weeks * 7);
        saltWaterTank.tankPtr->ageTank(weeks * 7);
    }
}
