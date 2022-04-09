#include "Museum.h"

Museum::Museum()
{
    std::cout << "a Museum object was created" << std::endl; 
}

Museum::~Museum()
{
    std::cout << "a Museum object was destroyed" << std::endl; 
}

float Museum::chargeVisitor(const float amountToCharge, Museum::Visitor visitor)
{
    std::cout << "Museum::chargeVisitor() a vistor named '" << visitor.name << "' was charged $" << amountToCharge << std::endl; 
    return visitor.payAdmissionFee(amountToCharge);
}

void Museum::addOrRemoveEmployees(const int numberOfEmployees)
{
    employeeCount += numberOfEmployees;
}

void Museum::lobbyPoliticians(const float bribeAmount)
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

float Museum::Visitor::payAdmissionFee(const float feeAmount)
{
    ++timesVisited;
    std::cout   << "Museum::Vistor:payAdmissionFee() - A visitor named '" << name << "' payed an admmission fee of $"
                << std::fixed << feeAmount << " and has now visited " << timesVisited << " times" << std::endl;
    return feeAmount;
}

void Museum::Visitor::viewExhibit(const int exhibitNum)
{
    std::cout << "Museum::Vistor:viewExhibit() - A visitor named '" << name << "' viewed exhibit # " << exhibitNum << std::endl;
}

void Museum::Visitor::payVendor(const int vendorID, const float amount) const
{
    std::cout   << "Museum::Vistor:payVendor() - A visitor named '" << name << "' payed vendor # " << vendorID
                << " $" << std::fixed << std::setprecision(2) << amount << std::endl;
}

void Museum::simulateMonths(const int months)
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
