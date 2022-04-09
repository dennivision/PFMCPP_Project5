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

    struct Visitor;

    Museum();
    ~Museum();

    float chargeVisitor(const float amountToCharge, Visitor visitor) ;
    void addOrRemoveEmployees(const int numberOfEmployees);
    void lobbyPoliticians(const float bribeAmount);

    void simulateMonths(const int months);

    void printEmployeeCount(const std::string name);
    JUCE_LEAK_DETECTOR(Museum)
};

struct Museum::Visitor
{
    std::string name, nationality;
    int timesVisited, age;
    float satisfaction = 0.5f;

    Visitor();
    Visitor(std::string n);
    ~Visitor();

    float payAdmissionFee(const float feeAmount);        
    void viewExhibit(const int exhibitNum);
    void payVendor(const int vendorID, const float amount) const;
};
