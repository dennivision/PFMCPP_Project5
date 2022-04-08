/*
 Project 5: Part 4 / 4
 video: Chapter 3 Part 7

 Create a branch named Part4
 
 Don't #include what you don't use
 
 1) Your task is to refactor your Chapter 3 Part 4 task into separate source and header files.
         Add files via the pane on the left.
 
 2) Put all of your declarations for each class in .h files
         One header file per class ( i.e. Raider.h for a class named "Raider" )
         Don't forget the '#pragma once'
 
 3) Put all of your implementations in .cpp files.
         one cpp file per class ( i.e. Raider.cpp for a class named "Raider" )
 
 4) Put all of your Wrapper classes in a single Wrappers.h file
         if you implemented your wrapper class functions in-class, you'll need to move them to Wrappers.cpp, which goes along with instruction 5): 
 
 5) NO IN-CLASS IMPLEMENTATION ALLOWED.
         the only exception is the existing Atomic.h and LeakedObjectDetector.h
        Chances are extremely high that you implemented your 
        wrapper class functions in-class, because that is what 
        everyone does after watching the video where I implemented 
        them in-class.
 
 6) for every .cpp file you have to make, insert it into the .replit file after 'main.cpp'.  Don't forget the spaces between file names.
 If you need help with this step, send me a DM.

 7) When you add the #include statements for your refactored source files into main.cpp: 
        '#include "Wrappers.h"' should be the first file that you include after LeakedObjectDetector.h
 
 8) Go through every cpp file and header file. check all function implementations for the following:
        Can this function argument be declared as 'const'? 
        Can this function be declared as 'const'?
        You learned about 'const' function arguments and 'const' functions in Project 5 Part 3
        As a refresher:
            If you aren't modifying the passed-in object inside the function, pass by 'const reference'.
            Marking a function parameter as 'const' means that you are promising that the parameter will not be modified.
            Additionally, you can mark class member functions as 'const'
            If you do this, you are promising that the member function will not modify any member variables.

        Mark every member function that is not modifying any member variables as 'const'
        Mark every function parameter that is not modified inside the function as 'const'
*/
#if false
//a function where the argument is passed by const-ref.
void Foo::someMemberFunction(const Axe& axe);

//a member function that is marked const, meaning it will not modify any member variables of the 'Axe' class.
void Axe::aConstMemberFunction() const { }
#endif
/*
 9) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Remember, your Chapter 3 Part 4 task worked when it was all in one file. so you shouldn't need to edit any of it.  
         just split it up into source files and provide the appropriate #include directives.
         tip: you cannot forward-declare nested types!  
         The file that a nested type is defined in MUST be included wherever that nested type is written.
 */






#include <iostream>
#include <iomanip>
#include <vector>
#include "LeakedObjectDetector.h"
/*
 copied UDT 1:
 */

struct AquariumTank
{
    float waterCapacity, pHLevel, currentWaterLevel, evaporationRate;
    int fishLivingIn;

    struct Fish
    {
        std::string name, breed;
        float maxSalinity, age, maxAge;
        
        Fish();
        ~Fish();

        bool canLiveInThisWater(float waterPH, float waterSalinity);
        void ageFish(float amountOfTime);
        bool isStillAlive(float waterPH, float waterSalinity);
    };

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

// WRAPPER CLASSES
struct TankWrapper
{
    TankWrapper(AquariumTank* ptr) : tankPtr(ptr) {}
    ~TankWrapper()
    {
        delete tankPtr;
    }
    AquariumTank* tankPtr = nullptr;
};

/*
 copied UDT 2:
 */
struct Museum
{
    int exhibitCount = 5;
    int employeeCount = 0;
    float UtilityCost = 3500.f;
    float monthlyRetailIncome = 5000.f;
    float monthlyGovernmentSubsidy = 15000;

    float balance = 0.f;
    float averageSalary = 3000.f;
    float entranceFee = 25.f;

    struct Visitor
    {
        std::string name, nationality;
        int timesVisited, age;
        float satisfaction = 0.5f;

        Visitor();
        Visitor(std::string n);
        ~Visitor();

        float payAdmissionFee(float feeAmount);        
        void viewExhibit(int exhibitNum);
        void payVendor(int vendorID, float amount);
    };

    Museum();
    ~Museum();

    float chargeVisitor(float amountToCharge, Visitor visitor) ;
    void addOrRemoveEmployees(int numberOfEmployees);// { employeeCount += numberOfEmployees; }
    void lobbyPoliticians(float bribeAmount);

    void simulateMonths(int months);

    void printEmployeeCount(std::string name);
    JUCE_LEAK_DETECTOR(Museum)
};

Museum::Museum()
{
    std::cout << "a Museum object was created" << std::endl; 
}

Museum::~Museum()
{
    std::cout << "a Museum object was destroyed" << std::endl; 
}

float Museum::chargeVisitor(float amountToCharge, Museum::Visitor visitor)
{
    std::cout << "Museum::chargeVisitor() a vistor named '" << visitor.name << "' was charged $" << amountToCharge << std::endl; 
    return visitor.payAdmissionFee(amountToCharge);
}

void Museum::addOrRemoveEmployees(int numberOfEmployees)
{
    employeeCount += numberOfEmployees;
}

void Museum::lobbyPoliticians(float bribeAmount)
{
    if(bribeAmount > 10000.f)
    {
        std::cout << "Museum::lobbyPoliticians() success! $" << std::fixed << bribeAmount << " dollars was a large enough bribe!" << std::endl;std::cout << std::defaultfloat; // reset the io stream to clear formatting 
        monthlyGovernmentSubsidy += 2500;
        return;
    }
    std::cout << "Museum::lobbyPoliticians() sad trombone sound. Better luck next time cheapskate." << std::endl; 
}

Museum::Visitor::Visitor() : name("visitor"), nationality("unknown"), timesVisited(0), age(0), satisfaction(0.5f)
{
    std::cout << "a Museum::Visitor named '" << name << "' from the country '" << nationality << "' was created" << std::endl; 
}
Museum::Visitor::Visitor(std::string n) : name(n), nationality("unknown"), timesVisited(0), age(0), satisfaction(0.5f)
{
    std::cout << "a Museum::Visitor named '" << name << "' from the country '" << nationality << "' was created" << std::endl; 
}
Museum::Visitor::~Visitor()
{
    std::cout << "a Museum::Visitor named '" << name << "' from the country '" << nationality << "' was destroyed" << std::endl; 
}

float Museum::Visitor::payAdmissionFee(float feeAmount)
{
    ++timesVisited; // bit confused why this doesn't appear to update the timesVisited int
    std::cout   << "Museum::Vistor:payAdmissionFee() - A visitor named '" << name << "' payed an admmission fee of $"
                << std::fixed << feeAmount << " and has now visited " << timesVisited << " times" << std::endl;
    return feeAmount;
}

void Museum::Visitor::viewExhibit(int exhibitNum)
{
    std::cout << "Museum::Vistor:viewExhibit() - A visitor named '" << name << "' viewed exhibit # " << exhibitNum << std::endl;
}

void Museum::Visitor::payVendor(int vendorID, float amount)
{
    std::cout   << "Museum::Vistor:payVendor() - A visitor named '" << name << "' payed vendor # " << vendorID
                << " $" << std::fixed << std::setprecision(2) << amount << std::endl;
}

void Museum::simulateMonths(int months)
{
    int visitors = 0;
    float startingBalance = balance;
    int month = 0;
    while(month < months)
    {
        ++month;
        float visitorsThisMonth = monthlyRetailIncome / entranceFee;
        //float deviation = visitorsThisMonth * 20 / 100;
        //visitorsThisMonth = (rand() % static_cast<int>(deviation) ) + (visitorsThisMonth - (deviation / 2)); // much more interesting
        visitorsThisMonth += (rand() % 200 ) - 100; // vary visitor count from ~ -100 to +100 of calculated value
        std::cout << "In month " << month << " there were " << visitorsThisMonth << " visitors" << std::endl;
        float lastVisitor = visitors + visitorsThisMonth;
        while(visitors <= lastVisitor)
        {
            ++visitors;
            /*
            Visitor x;
            balance += chargeVisitor(entranceFee, x);
            */
            balance += entranceFee; // just to save output lines here
        }
        balance += monthlyGovernmentSubsidy;
        if(balance < (employeeCount * averageSalary))
        {
            std::cout << "Museum cant pay " << employeeCount << " employees. Max it can pay is " << (balance / averageSalary) << std::endl;
            float maxEmployees = balance/averageSalary;
            int firedEmployees = 0;
            while(employeeCount > maxEmployees)
            {
                --employeeCount;
                ++firedEmployees;
            }
            std::cout << "Had to fire " << firedEmployees << " employees" << std::endl;
        }
        balance -= employeeCount * averageSalary;

        std::cout << "Month " << month << " balance is  $" << std::fixed << std::setprecision(2) << balance << std::endl;
    }
    monthlyRetailIncome = ((balance - (monthlyGovernmentSubsidy * month) + (employeeCount * averageSalary * month) - startingBalance) /  month);
    std::cout    << "After " << month << " months the musuem had " << visitors << " visitors and now has a balance of $"
                << std::fixed << balance << " and the average monthly retail income is now $"
                << monthlyRetailIncome << std::endl;

}

void Museum::printEmployeeCount(std::string name)
{
    std::cout << "Museum " << name << " now has " << this->employeeCount << " employees" << std::endl;
}

struct MuseumWrapper
{
    MuseumWrapper(Museum* ptr) : museumPtr(ptr) {}
    ~MuseumWrapper()
    {
        delete museumPtr;
    }
    Museum* museumPtr = nullptr;
};

/*
 copied UDT 3:
 */
struct FreightTrain
{
    int numberOfLocomotives = 1;
    int numberOfFreightCars = 1;
    float maxCargoWeight { numberOfLocomotives * 8000.f };
    float grossCargoWeight { numberOfFreightCars * 110.f };
    std::string conductorName = "conductor";

    FreightTrain();
    FreightTrain(int locomotives, int cars, std::string conductor);
    ~FreightTrain();

    void proceedToNextStop();
    void pickupOrDropoffCars(int numOfCars);
    void blowAirHorn(float durationInSeconds);
    void proceedSomeStops(unsigned long stops, std::vector<int> pickupDropOffList);

    void printMessage(std::string name);
    JUCE_LEAK_DETECTOR(FreightTrain)
};

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

void FreightTrain::pickupOrDropoffCars(int numOfCars)
{
    numberOfFreightCars += numOfCars;
    if (numberOfFreightCars < 0)
        numberOfFreightCars = 0;

    std::cout << "FreightTrain::pickupOrDropoffCars() called - train now has " << numberOfFreightCars << " cars" << std::endl; 
}

void FreightTrain::blowAirHorn(float durationInSeconds)
{
    if (durationInSeconds > 0.f)
    {
        std::cout << "FreightTrain::blowAirHorn() called - the horn toots for " << durationInSeconds << " seconds." << std::endl; 
    }
}

void FreightTrain::proceedSomeStops(unsigned long stops, std::vector<int> pickupDropoffList)
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

void FreightTrain::printMessage(std::string name)
{
    std::cout   << name <<" object has " << this->numberOfLocomotives << " locomotives and "
                << this->numberOfFreightCars << " freight cars and its conductors name is " << this->conductorName << std::endl;
}

struct TrainWrapper
{
    TrainWrapper(FreightTrain* ptr) : trainPtr(ptr){}
    ~TrainWrapper()
    {
        delete trainPtr;
    }
    FreightTrain* trainPtr = nullptr;
};

/*
 new UDT 4:
 with 2 member functions
 */
struct FreightLine
{
    TrainWrapper train1 = TrainWrapper(new FreightTrain(4,20,"Fred"));
    TrainWrapper train2 = TrainWrapper(new FreightTrain(2,25,"Bob"));
    TrainWrapper train3 = TrainWrapper(new FreightTrain());
    //TrainWrapper train3(new FreightTrain()); // not sure I understand why I can't declare and initialize wrapper class member variables like this

    FreightLine();
    ~FreightLine();

    bool dispatchTrain(int train, std::vector<int> pickupDropoffList);
    bool dispatchTrain(FreightTrain& train, std::vector<int> pickupDropoffList);
    void describeTrain(const FreightTrain& train);
    JUCE_LEAK_DETECTOR(FreightLine)
};

FreightLine::FreightLine()
{
    std::cout   << "A new FreightLine exists with three trains whose conductors are named "
                << train1.trainPtr->conductorName << ", " <<train2.trainPtr->conductorName << ", and " << train3.trainPtr->conductorName << std::endl;
}

FreightLine::~FreightLine()
{
     std::cout   << "A new FreightLine was destroyed" << std::endl;
}

bool FreightLine::dispatchTrain(int train, std::vector<int> pickupDropoffList)
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

bool FreightLine::dispatchTrain(FreightTrain& train, std::vector<int> pickupDropoffList)
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

struct FreightLineWrapper
{
    FreightLineWrapper(FreightLine* ptr) : freightLinePtr(ptr){}
    ~FreightLineWrapper()
    {
        delete freightLinePtr;
    }
    FreightLine* freightLinePtr = nullptr;
};
        
/*
 new UDT 5:
 with 2 member functions
 */
struct AquariumStore
{
    TankWrapper freshWaterTank1 = TankWrapper(new AquariumTank(120.f));
    TankWrapper freshWaterTank2 = TankWrapper(new AquariumTank(55.f));
    TankWrapper freshWaterTank3 = TankWrapper(new AquariumTank(25.f));
    TankWrapper saltWaterTank = TankWrapper(new AquariumTank(180.f));
    AquariumStore();
    ~AquariumStore();

    void topOffTanks();
    void ageTanks(int weeks);
    JUCE_LEAK_DETECTOR(AquariumStore)
};

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
    while(freshWaterTank1.tankPtr->currentWaterLevel < 1.f)  { freshWaterTank1.tankPtr->addWater(5.f); }
    while(freshWaterTank2.tankPtr->currentWaterLevel < 1.f)  { freshWaterTank2.tankPtr->addWater(5.f); }
    while(freshWaterTank3.tankPtr->currentWaterLevel < 1.f)  { freshWaterTank3.tankPtr->addWater(5.f); }
    while(saltWaterTank.tankPtr->currentWaterLevel < 1.f)    { saltWaterTank.tankPtr->addWater(5.f); }
}

void AquariumStore::ageTanks(int weeks)
{
    if (weeks > 0)
    {
        freshWaterTank1.tankPtr->ageTank(weeks * 7);
        freshWaterTank2.tankPtr->ageTank(weeks * 7);
        freshWaterTank3.tankPtr->ageTank(weeks * 7);
        saltWaterTank.tankPtr->ageTank(weeks * 7);
    }
}

struct AquariumStoreWrapper
{
    AquariumStoreWrapper(AquariumStore* ptr) : aquariumStorePtr(ptr){}
    ~AquariumStoreWrapper()
    {
        delete aquariumStorePtr;
    }
    AquariumStore* aquariumStorePtr = nullptr;
};

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */
void printSpacer(std::string msg)
{
    std::cout << std::endl;
    std::cout << "-------- " << msg << " --------" << std::endl;
    std::cout << std::endl;
}

void printEmptyLine()
{
    std::cout << std::endl;
}

#include <iostream>
int main()
{
    //srand(  time( nullptr ) );

    printSpacer("AquariumTank object testing");

    AquariumTank::Fish fish1,fish2;

    printEmptyLine();

    fish1.name = "uno";
    fish2.name = "due";

    fish1.ageFish(1.f);
    fish2.ageFish(1.f);

    printEmptyLine();;

    TankWrapper tank1 (new AquariumTank());
    TankWrapper tank2 (new AquariumTank());

    printEmptyLine();

    tank1.tankPtr->waterCapacity = 55.f;
    tank1.tankPtr->currentWaterLevel = .5f;
    tank1.tankPtr->addWater(20.f);
    tank1.tankPtr->addFish(fish1, 10);
    tank1.tankPtr->adjustPH(-.5f);

    tank1.tankPtr->ageTank(10);

    printEmptyLine();

    tank2.tankPtr->addWater(5.f);
    tank2.tankPtr->adjustPH(1.5f);
    tank2.tankPtr->addFish(fish2, 5);
    tank2.tankPtr->adjustPH(-1.f);
    tank2.tankPtr->addFish(fish2, 4);

    tank2.tankPtr->ageTank(120);

    printSpacer("Museum Object Testing");

    Museum::Visitor visitor1, visitor2;

    printEmptyLine();

    visitor1.name = "Bert";
    visitor2.name = "Ernie";

    MuseumWrapper m1(new Museum());
    MuseumWrapper m2(new Museum());
    m1.museumPtr->exhibitCount = 5;
    m2.museumPtr->exhibitCount = 10;

    printEmptyLine();

    m1.museumPtr->addOrRemoveEmployees(10);
    std::cout << "Museum m1 now has " << m1.museumPtr->employeeCount << " employees" << std::endl;
    m1.museumPtr->printEmployeeCount("m1");
    printEmptyLine();
    m1.museumPtr->addOrRemoveEmployees(-8);
    std::cout << "Museum m1 now has " << m1.museumPtr->employeeCount << " employees" << std::endl;
    m1.museumPtr->printEmployeeCount("m1");
    printEmptyLine();

    float m1Revenue = m1.museumPtr->chargeVisitor(10.f, visitor1);
    m1Revenue += m1.museumPtr->chargeVisitor(20.f, visitor2);
    std::cout << "Museum m1 extracted $" << std::fixed << m1Revenue << " from vistors" << std::defaultfloat << std::endl;
    m1.museumPtr->lobbyPoliticians(20000);

    m1.museumPtr->simulateMonths(6);

    printEmptyLine();

    m2.museumPtr->addOrRemoveEmployees(40);
    std::cout << "Museum m2 now has " << m2.museumPtr->employeeCount << " employees" << std::endl;
    m2.museumPtr->printEmployeeCount("m2");
    printEmptyLine();
    float m2Revenue = m2.museumPtr->chargeVisitor(25, visitor2);
    m2Revenue += m2.museumPtr->chargeVisitor(10.f, visitor1);
    std::cout << "Museum m2 extracted $" << std::fixed << m2Revenue << " from vistors" << std::defaultfloat << std::endl;
    m2.museumPtr->lobbyPoliticians(4999.5);
    m2.museumPtr->monthlyRetailIncome = 100000.f;
    m2.museumPtr->simulateMonths(12);
    m2.museumPtr->addOrRemoveEmployees(10);
    m2.museumPtr->simulateMonths(12);

    printEmptyLine();

    visitor1.viewExhibit(1);
    visitor1.viewExhibit(4);
    visitor1.payAdmissionFee(25.f);
    visitor1.payVendor(4, 4.99f);


    printSpacer("FreightTrain object testing");

    TrainWrapper train1(new FreightTrain());
    train1.trainPtr->pickupOrDropoffCars(50);
    train1.trainPtr->proceedToNextStop();
    train1.trainPtr->blowAirHorn(1.f);

    std::cout   << "train1 object has " << train1.trainPtr->numberOfLocomotives << " locomotives and "
                << train1.trainPtr->numberOfFreightCars << " freight cars and its conductors name is " << train1.trainPtr->conductorName << std::endl;

    train1.trainPtr->printMessage("train1");
    printEmptyLine();

    printEmptyLine();

    TrainWrapper train2(new FreightTrain());
    train2.trainPtr->conductorName = "bob";
    train2.trainPtr->pickupOrDropoffCars(80);
    train2.trainPtr->proceedToNextStop();
    train2.trainPtr->pickupOrDropoffCars(-40);
    train2.trainPtr->blowAirHorn(1.f);

    std::cout   << "train2 object has " << train2.trainPtr->numberOfLocomotives << " locomotives and "
                << train2.trainPtr->numberOfFreightCars << " freight cars and its conductors name is " << train2.trainPtr->conductorName << std::endl;

    train2.trainPtr->printMessage("train2");
    printEmptyLine();

    printEmptyLine();
    std::vector<int> dropofflist{5,-1,4,-4,3};
    train2.trainPtr->proceedSomeStops(5, dropofflist);

    printSpacer("FreightLine object testing");

    FreightLineWrapper line(new FreightLine());
    std::vector<int> lineOrderList{ 10, 0, -5, -15, 20, -25, 40, 10, 0, -6, -38  };
    std::vector<int> lineOrderList2{ 10, -10, 5, 15, 3, 1  };

    line.freightLinePtr->dispatchTrain(0, lineOrderList);
    printEmptyLine();
    line.freightLinePtr->dispatchTrain(1, lineOrderList2);
    printEmptyLine();

    line.freightLinePtr->describeTrain(*(line.freightLinePtr->train1.trainPtr)); // this feels wrong

    printSpacer ("AquariumStore object testing");

    //AquariumStore store;
    AquariumStoreWrapper store(new AquariumStore());
    printEmptyLine();
    store.aquariumStorePtr->topOffTanks();
    printEmptyLine();
    store.aquariumStorePtr->ageTanks(12);
    printEmptyLine();
    store.aquariumStorePtr->topOffTanks();
    printEmptyLine();

    std::cout << "good to go!" << std::endl;

    printSpacer("Everything goes out of scope now");
}
