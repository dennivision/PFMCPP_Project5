#pragma once
#include <iostream>
#include <iomanip>
#include "LeakedObjectDetector.h"

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
