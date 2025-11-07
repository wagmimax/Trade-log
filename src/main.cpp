#include "User.h"

//TO BUILD:
//travel to build dir and run:
//cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE="C:/Users/maxxk/OneDrive/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..
//ninja
//then just run TradeLog.exe in cmd

int main()
{   
    int userInp = 0;
    User user;
    std::cout << "\nStrict risk management trade log. Enter -1 to exit program.\n";
    user.printLog();
    
    while(userInp != -1)
    {   
        std::cout << "\n1. Setup trade\n2. Log trade\n3. Print trade log\n4. Set account details\n";
        std::cin >> userInp;

        // Check if input is valid
        if (std::cin.fail())
        {
            // Clear the error state
            std::cin.clear();
            // Ignore the rest of the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input\n";
            userInp = 0; // Reset userInp to avoid unexpected behavior
            continue;
        }
        //main control loop switch statement
        switch(userInp)
        {
            case 1: //trade setup
            {
                std::stringstream stopLossStream;
                double stopLoss;

                //get users stoploss
                std::cout << "\nEnter stoploss%: ";
                std::cin >> stopLoss;

                //error handling
                if (std::cin.fail())
                {
                    // Clear the error state
                    std::cin.clear();
                    // Ignore the rest of the input buffer
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\nInvalid input\n";
                    continue;
                }

                stopLossStream << std::fixed << std::setprecision(2) << user.calculatePosition(stopLoss); //set to the second decimal place

                //output details
                std::cout << "Position size: $" << stopLossStream.str();
                std::cout << "\nRecommended minimum target profit%: " << (stopLoss + user.getFees())*3 << std::endl; // 1:3 risk:reward ratio    
            }break;
            case 2: //log trade
            {
                double PNL;

                std::cout << "\nEnter trade PNL: ";
                std::cin >> PNL;

                if (std::cin.fail())
                {
                    // Clear the error state
                    std::cin.clear();
                    // Ignore the rest of the input buffer
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\nInvalid input\n";
                    continue;
                }

                user.logTrade(PNL);
            }break;
            case 3: //print log
            {
                user.printLog();
            }break;
            case 4: //set account details
            {
                double bal, fee;
                int lev, detailSelection;
                std::cout << "\nNOTE: Risk is automatic and cannot be changed\n1. Set account balance\n2. Set leverage\n3. Set exchange fees\n";
                std::cin >> detailSelection;
                
                if (std::cin.fail())
                {
                    // Clear the error state
                    std::cin.clear();
                    // Ignore the rest of the input buffer
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\nInvalid input\n";
                    detailSelection = 0; // Reset detailSelection to avoid unexpected behavior
                    continue;
                }

                switch(detailSelection)
                {
                    case 1:
                    {
                        std::cout << "\nEnter account balance: ";
                        std::cin >> bal;
                        user.setBalance(bal);
                    }break;
                    case 2:
                    {
                        std::cout << "\nEnter leverage: ";
                        std::cin >> lev;
                        user.setLeverage(lev);
                    
                    }break;
                    case 3:
                    {
                        std::cout << "\nEnter exchange fees (decimal wise): ";
                        std::cin >> fee;
                        user.setFees(fee);
                    }break;
                }
            }break;
        }

    }

    return 0;
}