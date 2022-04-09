#include "Wrappers.h"

#include "AquariumTank.h"
#include "Museum.h"
#include "FreightTrain.h"
#include "FreightLine.h"

TankWrapper::TankWrapper(AquariumTank* ptr) : tankPtr(ptr) {}
TankWrapper::~TankWrapper()
{
    delete tankPtr;
}

MuseumWrapper::MuseumWrapper(Museum* ptr) : museumPtr(ptr) {}
MuseumWrapper::~MuseumWrapper()
{
    delete museumPtr;
}

TrainWrapper::TrainWrapper(FreightTrain* ptr) : trainPtr(ptr){}
TrainWrapper::~TrainWrapper()
{
    delete trainPtr;
}

FreightLineWrapper::FreightLineWrapper(FreightLine* ptr) : freightLinePtr(ptr){}
FreightLineWrapper::~FreightLineWrapper()
{
    delete freightLinePtr;
}

AquariumStoreWrapper::AquariumStoreWrapper(AquariumStore* ptr) : aquariumStorePtr(ptr){}
AquariumStoreWrapper::~AquariumStoreWrapper()
{
    delete aquariumStorePtr;
}
