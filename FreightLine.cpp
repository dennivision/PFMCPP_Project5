#include "FreightLine.h"
//#include "FreightTrain.h"

FreightLine::FreightLine()
{
    std::cout   << "A new FreightLine exists with three trains whose conductors are named "
                << train1.trainPtr->conductorName << ", " <<train2.trainPtr->conductorName << ", and " << train3.trainPtr->conductorName << std::endl;
}

FreightLine::~FreightLine()
{
     std::cout   << "A new FreightLine was destroyed" << std::endl;
}

bool FreightLine::dispatchTrain(const int train, const std::vector<int>& pickupDropoffList)
{
    switch(train)
    {
        case (0):
        {
            train1.trainPtr->proceedSomeStops(pickupDropoffList.size(), pickupDropoffList);
            break;
        }
        case (1):
        {
            train2.trainPtr->proceedSomeStops(pickupDropoffList.size(), pickupDropoffList);
            break;
        }
        case (3):
        {
            train3.trainPtr->proceedSomeStops(pickupDropoffList.size(), pickupDropoffList);
            break;
        }
        default:
        {
            return false;
        }
    }
    return true;
}

bool FreightLine::dispatchTrain(FreightTrain& train, const std::vector<int>& pickupDropoffList)
{
    train.proceedSomeStops(pickupDropoffList.size(), pickupDropoffList);
    return true;
}

void FreightLine::describeTrain(const FreightTrain& train)
{
    std::cout << "----FreightLine::DescribeTrain()----" << std::endl;
    std::cout << "The trains conductor is named " << train.conductorName << std::endl;
    std::cout << "This train has " << train.numberOfLocomotives << " locomotives and " << train.numberOfFreightCars << " cars." << std::endl;
    std::cout    << "It can pull a maximum of " << std::fixed << train.maxCargoWeight 
            << " tons and it is currently carrying " << train.grossCargoWeight << "tons" << std::endl;
    for(int i = 0; i < train.numberOfLocomotives; ++i)
    {
        std::cout << "/_" << i+1 << "_\\";
    }
    for(int i = 0; i < train.numberOfFreightCars; ++i)
    {
        std::cout << "|" << i+1 << "|";
    }
    std::cout << std::endl;
    std::cout << "------------------------------------" << std::endl << std::endl;
}
