#include "FreightTrain.h"

FreightTrain::FreightTrain()
{
    std::cout << "FreightTrain constructor called - a FreightTrain object was created" << std::endl;
}
FreightTrain::FreightTrain(int locomotives, int cars, std::string conductor) :
    numberOfLocomotives( locomotives ),
    numberOfFreightCars( cars ),
    conductorName(conductor)
{
    std::cout << "FreightTrain constructor called - a FreightTrain was created and the conductors name is " << conductorName << std::endl;
}

FreightTrain::~FreightTrain()
{
    std::cout << "FreightTrain object destroyed" << std::endl;
}

void FreightTrain::proceedToNextStop()
{
    blowAirHorn(5.f);
    std::cout << "FreightTrain::proceedToNextStop() - the train proceeds to the next stop" << std::endl;
}

void FreightTrain::pickupOrDropoffCars(const int numOfCars)
{
    numberOfFreightCars += numOfCars;
    if (numberOfFreightCars < 0)
        numberOfFreightCars = 0;

    std::cout << "FreightTrain::pickupOrDropoffCars() called - train now has " << numberOfFreightCars << " cars" << std::endl; 
}

void FreightTrain::blowAirHorn(const float durationInSeconds)
{
    if (durationInSeconds > 0.f)
    {
        std::cout << "FreightTrain::blowAirHorn() called - the horn toots for " << durationInSeconds << " seconds." << std::endl; 
    }
}

void FreightTrain::proceedSomeStops(const unsigned long stops, const std::vector<int> pickupDropoffList)
{
    unsigned long stopsTraveled = 0;
    int freightCarDelta = 0;
    while(stopsTraveled < stops)
    {
        proceedToNextStop();
        if(stopsTraveled < pickupDropoffList.size() )
        {
            pickupOrDropoffCars(pickupDropoffList[stopsTraveled]);
            freightCarDelta += pickupDropoffList[stopsTraveled];
        }
        ++stopsTraveled;
    }
    std::cout << "Train Traveled a total of " << stopsTraveled << " out of " << stops << " and the car count changed by " << freightCarDelta << std::endl;
}

void FreightTrain::printMessage(const std::string name) const
{
    std::cout   << name <<" object has " << this->numberOfLocomotives << " locomotives and "
                << this->numberOfFreightCars << " freight cars and its conductors name is " << this->conductorName << std::endl;
}
