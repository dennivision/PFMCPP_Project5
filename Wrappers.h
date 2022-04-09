#pragma once

struct AquariumTank;
struct Museum;
struct FreightTrain;
struct FreightLine;
struct AquariumStore;

struct TankWrapper
{
    TankWrapper(AquariumTank* ptr);
    ~TankWrapper();
    AquariumTank* tankPtr = nullptr;
};

struct MuseumWrapper
{
    MuseumWrapper(Museum* ptr);
    ~MuseumWrapper();
    Museum* museumPtr = nullptr;
};

struct TrainWrapper
{
    TrainWrapper(FreightTrain* ptr);
    ~TrainWrapper();
    FreightTrain* trainPtr = nullptr;
};

struct FreightLineWrapper
{
    FreightLineWrapper(FreightLine* ptr);
    ~FreightLineWrapper();
    FreightLine* freightLinePtr = nullptr;
};

struct AquariumStoreWrapper
{
    AquariumStoreWrapper(AquariumStore* ptr);
    ~AquariumStoreWrapper();
    AquariumStore* aquariumStorePtr = nullptr;
};


#include "AquariumTank.h"
#include "Museum.h"
#include "FreightTrain.h"
#include "FreightLine.h"
#include "AquariumStore.h"
