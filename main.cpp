/*
 Project 5: Part 3 / 4
 video: Chapter 3 Part 4: 

Create a branch named Part3

 the 'new' keyword

 1) add #include "LeakedObjectDetector.h" to main
 
 2) Add 'JUCE_LEAK_DETECTOR(OwnerClass)' at the end of your UDTs.
 
 3) write the name of your class where it says "OwnerClass"
 
 4) write wrapper classes for each type similar to how it was shown in the video
 
 5) update main() 
      replace your objects with your wrapper classes, which have your UDTs as pointer member variables.
      
    This means if you had something like the following in your main() previously: 
*/
#if false
 Axe axe;
 std::cout << "axe sharpness: " << axe.sharpness << "\n";
 #endif
 /*
    you would update that to use your wrappers:
    
 */

#if false
AxeWrapper axWrapper( new Axe() );
std::cout << "axe sharpness: " << axWrapper.axPtr->sharpness << "\n";
#endif
/*
notice that the object name has changed from 'axe' to 'axWrapper'
You don't have to do this, you can keep your current object name and just change its type to your Wrapper class

6) If you have a class that has a nested class in it, and an instantiation of that nested class as a member variable, 
    - you do not need to write a Wrapper for that nested class
    - you do not need to replace that nested instance with a wrapped instance.
    If you want an explanation, message me in Slack

7) If you were using any UDTs as function arguments like this:
*/
#if false
void someMemberFunction(Axe axe);
#endif
/*
  Pass those arguments by Reference now that you know what references are (Project 6 Part 2).
*/
#if false
void someMemberFunction(Axe& axe);
#endif
/*
If you aren't modifying the passed-in object inside the function, pass by const reference.
*/
#if false
void someMemberFunction(const Axe& axe);
#endif
/*
 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 see here for an example: https://repl.it/@matkatmusic/ch3p04example

 Clear any warnings about exit-time-destructors.
 Suppress them by adding -Wno-exit-time-destructors to the .replit file with the other warning suppression flags
 */




#include <iostream>
#include <iomanip>
#include <vector>
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
        int visitorsThisMonth = monthlyRetailIncome / entranceFee;
        int deviation = visitorsThisMonth * 20 / 100;
        visitorsThisMonth = (rand() % deviation) + (visitorsThisMonth - (deviation / 2));
        std::cout << "In month " << month << " there were " << visitorsThisMonth << " visitors" << std::endl;
        int lastVisitor = visitors + visitorsThisMonth;
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
            int employeesToFire = employeeCount - (balance / averageSalary);
            employeeCount -= employeesToFire;
            std::cout << "Had to fire " << employeesToFire << " employees" << std::endl;
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

/*
 new UDT 4:
 with 2 member functions
 */
struct FreightLine
{
    FreightTrain train1 { 4, 20, "Fred" };
    FreightTrain train2 { 2, 25, "Bob" };
    FreightTrain train3;

    FreightLine();
    ~FreightLine();

    bool DispatchTrain(int train, std::vector<int> pickupDropoffList);
    void DescribeTrain(FreightTrain train);
};

FreightLine::FreightLine()
{
    std::cout   << "A new FreightLine exists with three trains whose conductors are named "
                << train1.conductorName << ", " <<train2.conductorName << ", and " << train3.conductorName << std::endl;
}

FreightLine::~FreightLine()
{
     std::cout   << "A new FreightLine was destroyed" << std::endl;
}

bool FreightLine::DispatchTrain(int train, std::vector<int> pickupDropoffList)
{
    switch(train)
    {
        case (0):
        {
            train1.proceedSomeStops(pickupDropoffList.size(), pickupDropoffList);
            break;
        }
        case (1):
        {
            train2.proceedSomeStops(pickupDropoffList.size(), pickupDropoffList);
            break;
        }
        case (3):
        {
            train3.proceedSomeStops(pickupDropoffList.size(), pickupDropoffList);
            break;
        }
        default:
        {
            return false;
        }
    }
    return true;
}

void FreightLine::DescribeTrain(FreightTrain train)
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

/*
 new UDT 5:
 with 2 member functions
 */
struct AquariumStore
{
    AquariumTank freshWaterTank1{120.f};
    AquariumTank freshWaterTank2{55.f};
    AquariumTank freshWaterTank3{25.f};
    AquariumTank saltWaterTank{180.f};

    AquariumStore();
    ~AquariumStore();

    void topOffTanks();
    void ageTanks(int weeks);
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
    while(freshWaterTank1.currentWaterLevel < 1.f)  { freshWaterTank1.addWater(5.f); }
    while(freshWaterTank2.currentWaterLevel < 1.f)  { freshWaterTank2.addWater(5.f); }
    while(freshWaterTank3.currentWaterLevel < 1.f)  { freshWaterTank3.addWater(5.f); }
    while(saltWaterTank.currentWaterLevel < 1.f)    { saltWaterTank.addWater(5.f); }
}

void AquariumStore::ageTanks(int weeks)
{
    if (weeks > 0)
    {
        freshWaterTank1.ageTank(weeks * 7);
        freshWaterTank2.ageTank(weeks * 7);
        freshWaterTank3.ageTank(weeks * 7);
        saltWaterTank.ageTank(weeks * 7);
    }
}

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
    srand(  time( nullptr ) );

    printSpacer("AquariumTank object testing");

    AquariumTank::Fish fish1,fish2;

    printEmptyLine();

    fish1.name = "uno";
    fish2.name = "due";

    fish1.ageFish(1.f);
    fish2.ageFish(1.f);

    printEmptyLine();;

    AquariumTank tank1, tank2;

    printEmptyLine();

    tank1.waterCapacity = 55.f;
    tank1.currentWaterLevel = .5f;
    tank1.addWater(20.f);
    tank1.addFish(fish1, 10);
    tank1.adjustPH(-.5f);

    tank1.ageTank(10);

    printEmptyLine();

    tank2.addWater(5.f);
    tank2.adjustPH(1.5f);
    tank2.addFish(fish2, 5);
    tank2.adjustPH(-1.f);
    tank2.addFish(fish2, 4);

    tank2.ageTank(120);

    printSpacer("Museum Object Testing");

    Museum::Visitor visitor1, visitor2;

    printEmptyLine();

    visitor1.name = "Bert";
    visitor2.name = "Ernie";

    Museum m1, m2;
    m1.exhibitCount = 5;
    m2.exhibitCount = 10;

    printEmptyLine();

    m1.addOrRemoveEmployees(10);
    std::cout << "Museum m1 now has " << m1.employeeCount << " employees" << std::endl;
    m1.printEmployeeCount("m1");
    printEmptyLine();
    m1.addOrRemoveEmployees(-8);
    std::cout << "Museum m1 now has " << m1.employeeCount << " employees" << std::endl;
    m1.printEmployeeCount("m1");
    printEmptyLine();

    float m1Revenue = m1.chargeVisitor(10.f, visitor1);
    m1Revenue += m1.chargeVisitor(20.f, visitor2);
    std::cout << "Museum m1 extracted $" << std::fixed << m1Revenue << " from vistors" << std::defaultfloat << std::endl;
    m1.lobbyPoliticians(20000);

    m1.simulateMonths(6);

    printEmptyLine();

    m2.addOrRemoveEmployees(40);
    std::cout << "Museum m2 now has " << m2.employeeCount << " employees" << std::endl;
    m2.printEmployeeCount("m2");
    printEmptyLine();
    float m2Revenue = m2.chargeVisitor(25, visitor2);
    m2Revenue += m2.chargeVisitor(10.f, visitor1);
    std::cout << "Museum m2 extracted $" << std::fixed << m2Revenue << " from vistors" << std::defaultfloat << std::endl;
    m2.lobbyPoliticians(4999.5);
    m2.monthlyRetailIncome = 100000.f;
    m2.simulateMonths(12);
    m2.addOrRemoveEmployees(10);
    m2.simulateMonths(12);

    printEmptyLine();

    visitor1.viewExhibit(1);
    visitor1.viewExhibit(4);
    visitor1.payAdmissionFee(25.f);
    visitor1.payVendor(4, 4.99f);


    printSpacer("FreightTrain object testing");

    FreightTrain train1;
    train1.pickupOrDropoffCars(50);
    train1.proceedToNextStop();
    train1.blowAirHorn(1.f);

/*
    int numberOfLocomotives = 1;
    int numberOfFreightCars = 1;
    float maxCargoWeight { numberOfLocomotives * 8000.f };
    float grossCargoWeight { numberOfFreightCars * 110.f };
    std::string conductorName = "conductor";
*/
    std::cout   << "train1 object has " << train1.numberOfLocomotives << " locomotives and "
                << train1.numberOfFreightCars << " freight cars and its conductors name is " << train1.conductorName << std::endl;

    train1.printMessage("train1");
    printEmptyLine();

    printEmptyLine();

    FreightTrain train2;
    train2.conductorName = "bob";
    train2.pickupOrDropoffCars(80);
    train2.proceedToNextStop();
    train2.pickupOrDropoffCars(-40);
    train2.blowAirHorn(1.f);

    std::cout   << "train2 object has " << train2.numberOfLocomotives << " locomotives and "
                << train2.numberOfFreightCars << " freight cars and its conductors name is " << train2.conductorName << std::endl;

    train2.printMessage("train2");
    printEmptyLine();

    printEmptyLine();
    //int dropofflist[]{5,-1,4,-4,3}; 
    std::vector<int> dropofflist{5,-1,4,-4,3};
    train2.proceedSomeStops(5, dropofflist);

    printSpacer("FreightLine object testing");

    FreightLine line;
    std::vector<int> lineOrderList{ 10, 0, -5, -15, 20, -25, 40, 10, 0, -6, -38  };
    std::vector<int> lineOrderList2{ 10, -10, 5, 15, 3, 1  };

    line.DispatchTrain(0, lineOrderList);
    printEmptyLine();
    line.DispatchTrain(1, lineOrderList2);
    printEmptyLine();

    line.DescribeTrain(line.train1);

    printSpacer ("AquariumStore object testing");

    AquariumStore store;
    printEmptyLine();
    store.topOffTanks();
    printEmptyLine();
    store.ageTanks(12);
    printEmptyLine();
    store.topOffTanks();
    printEmptyLine();

    std::cout << "good to go!" << std::endl;

    printSpacer("Everything goes out of scope now");
}
