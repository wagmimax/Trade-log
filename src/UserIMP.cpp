#include "User.h"

void User::logTrade(const double& PNL)
{
    std::ofstream fout("../src/log.txt", std::ios::app);

    fout << PNL << " " << balance << " " << balance + PNL << " " << risk << "\n";

    fout.close();

    if(PNL < 0) //edit risk upon losing a trade
    {   

        std::vector<double> details;
        details.push_back(risk);
        details.push_back(balance);
        
        
        //riskSequence holds memory of risks set for each balance
        riskSequence.insert(riskSequence.begin(), details);

        //halve risk per losing trade until risk = 0.5 to flatten the curve on losing streaks (2 -> 1 -> 0.5)
        if(risk != 0.5)
        {   
            double newRisk = risk/2;
            setRisk(newRisk);
        }
    }
    if(PNL > 0)
    {
        double rsk, bal;
        for(int i = 0; i < riskSequence.size(); i++)
        {
            rsk = riskSequence[i][0];
            bal = riskSequence[i][1];
            if((balance + PNL) > bal)
            {
                setRisk(rsk);
                riskSequence.erase(riskSequence.begin());
                riskSequence.shrink_to_fit();
            }
        }
    }

    //update balance after logging it
    double newBalance = balance + PNL;
    setBalance(newBalance);
}

double User::calculatePosition(const double& stopLoss)
{
    double riskAmount = (risk / 100) * balance;
    double positionSize = riskAmount / (stopLoss + fees);
    return positionSize * leverage;  // Adjust final size by leverage
}

void User::printLog()
{   
    //Declarations
    std::ifstream fin("../src/log.txt");

    tabulate::Table table;
    std::stringstream balanceStream, riskStream, feesStream;
    int count = 0;

    //variables to be read from file
    double PNL, startBal, endBal, riskTarget;

    //set precision to 2 decimal places for neat output
    balanceStream << std::fixed << std::setprecision(2) << balance;
    riskStream << std::fixed << std::setprecision(2) << risk;
    feesStream << std::fixed << std::setprecision(2) << fees;

    //row displaying current account details
    table.add_row({"Balance: $" + balanceStream.str(), "Leverage: " + std::to_string(leverage), "Risk: " + riskStream.str() + "%", "Fees: " + feesStream.str() + "%", ""});

    //row to display labels
    table.add_row({"Trade number", "P/L", "Starting Balance", "Ending Balance", "Risk"});

    while(fin >> PNL >> startBal >> endBal >> riskTarget)
    {
        //declaring stringstream vars in loop ensures they are empty
        std::stringstream PNLstream, startBalStream, endBalStream, riskTargetStream;

        //convert to stream to set precision
        PNLstream << std::fixed << std::setprecision(2) << PNL;
        startBalStream << std::fixed << std::setprecision(2) << startBal;
        endBalStream << std::fixed << std::setprecision(2) << endBal;
        riskTargetStream << std::fixed << std::setprecision(2) << riskTarget;

        table.add_row({"#" + std::to_string(count + 1), "$" + PNLstream.str(), "$" + startBalStream.str(), "$" + endBalStream.str(), riskTargetStream.str() + "%"});

        count++;
    }

    std::cout << table << std::endl;

    fin.close();
}

double User::getBalance()
{
    return balance;
}

int User::getLeverage()
{
    return leverage;
}

double User::getRisk()
{
    return risk;
}

double User::getFees()
{
    return fees;
}

void User::setBalance(const double& bal)
{   
    balance = bal;

    std::ofstream fout("../src/accountDetails.txt");

    //override file with new value
    fout << "Balance: " << balance << std::endl;
    fout << "Leverage: " << leverage << std::endl;
    fout << "Risk: " << risk << std::endl;
    fout << "Fees: " << fees;

    fout.close();
}

void User::setLeverage(const int& lev)
{
    leverage = lev;

    std::ofstream fout("../src/accountDetails.txt");

    //override file with new value
    fout << "Balance: " << balance << std::endl;
    fout << "Leverage: " << leverage << std::endl;
    fout << "Risk: " << risk << std::endl;
    fout << "Fees: " << fees; 

    fout.close();
}

void User::setRisk(const double& rsk)
{
    risk = rsk;

    std::ofstream fout("../src/accountDetails.txt");

    //override file with new value
    fout << "Balance: " << balance << std::endl;
    fout << "Leverage: " << leverage << std::endl;
    fout << "Risk: " << risk << std::endl;
    fout << "Fees: " << fees;

    fout.close();
}

void User::setFees(const double& fee)
{
    fees = fee;

    std::ofstream fout("../src/accountDetails.txt");

    //override file with new value
    fout << "Balance: " << balance << std::endl;
    fout << "Leverage: " << leverage << std::endl;
    fout << "Risk: " << risk << std::endl; 
    fout << "Fees: " << fees;

    fout.close();
}

User::User()
{
    std::string line, balanceStr, leverageStr, riskStr, feesStr;
    std::ifstream fin("../src/accountDetails.txt");
    int start;

    std::getline(fin, line); // Read the first line for balance
    start = line.find_first_of(' ') + 1;    
    balanceStr = line.substr(start);    //split line into just the balance value
    balance = std::stod(balanceStr);

    std::getline(fin, line);
    start = line.find_first_of(' ') + 1;
    leverageStr = line.substr(start);
    leverage = std::stoi(leverageStr);

    std::getline(fin, line);
    start = line.find_first_of(' ') + 1;
    riskStr = line.substr(start);
    risk = std::stod(riskStr);

    std::getline(fin, line);
    start = line.find_first_of(' ') + 1;
    feesStr = line.substr(start);
    fees = std::stod(feesStr);

    fin.close();

    //get values for riskSequence
    std::ifstream fin2("../src/log.txt");
    double PNL, startBal, endBal, rsk;
    while(fin2 >> PNL >> startBal >> endBal >> rsk)
    {
        std::vector<double> details;
        details.push_back(rsk);
        details.push_back(startBal);
        riskSequence.insert(riskSequence.begin(), details);

        //if a winning trade is detected, losing streak is broken and the riskSequence is wiped
        if(PNL > 0)
        {
            riskSequence.clear();
            riskSequence.shrink_to_fit();
        }
    }

    fin2.close();
}

void User::print()
{
    for(int i = 0; i < riskSequence.size(); i++)
    {
        std::cout << riskSequence[i][0] << " " << riskSequence[i][1] << std::endl;
    }
}