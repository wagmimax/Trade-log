#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<cmath>
#include<vector>
#include<tabulate\table.hpp>

class User
{
public:
    void logTrade(const double& PNL);
    double calculatePosition(const double& stopLoss);
    void printLog();
    double getBalance();
    int getLeverage();
    double getRisk();
    double getFees();
    void setBalance(const double& bal);
    void setLeverage(const int& lev);
    void setRisk(const double& rsk);
    void setFees(const double& fee);
    void print();
    User();
private:
    double balance, risk, fees;
    int leverage;
    std::vector<std::vector<double>> riskSequence;
};