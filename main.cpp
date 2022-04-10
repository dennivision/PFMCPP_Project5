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

#include "LeakedObjectDetector.h"

#include "Wrappers.h"

// #include "AquariumTank.h"
// #include "Museum.h"
// #include "FreightTrain.h"
// #include "FreightLine.h"
// #include "AquariumStore.h"

        

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

    line.freightLinePtr->describeTrain(line.freightLinePtr->train1);

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
