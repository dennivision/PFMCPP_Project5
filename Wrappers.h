#pragma once

// struct AquariumTank;
// struct Museum;
// struct FreightTrain;
// struct FreightLine;

#include "AquariumTank.h"
#include "Museum.h"
#include "FreightTrain.h"
#include "FreightLine.h"

struct TankWrapper
{
    TankWrapper(AquariumTank* ptr) : tankPtr(ptr) {}
    ~TankWrapper()
    {
        delete tankPtr;
    }
    AquariumTank* tankPtr = nullptr;
};

struct MuseumWrapper
{
    MuseumWrapper(Museum* ptr) : museumPtr(ptr) {}
    ~MuseumWrapper()
    {
        delete museumPtr;
    }
    Museum* museumPtr = nullptr;
};

struct TrainWrapper
{
    TrainWrapper(FreightTrain* ptr) : trainPtr(ptr){}
    ~TrainWrapper()
    {
        delete trainPtr;
    }
    FreightTrain* trainPtr = nullptr;
};

struct FreightLineWrapper
{
    FreightLineWrapper(FreightLine* ptr) : freightLinePtr(ptr){}
    ~FreightLineWrapper()
    {
        delete freightLinePtr;
    }
    FreightLine* freightLinePtr = nullptr;
};
