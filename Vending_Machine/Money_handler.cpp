#ifndef _MONEY__
#define _MONEY__
#include <iostream>
#include <string>
#include <cstring>
#include "User.cpp"
class Money_handler
{
public:
    static double money_generator(std::string stringcoins)
    {
        int total_amount{};
        bool coin_validator = true;
        for (auto i : stringcoins)
        {
            i = i - '0';
            switch (i)
            {
            case 1:
            {
                total_amount += 1;
                break;
            }
            case 2:
            {
                total_amount += 5;
                break;
            }
            case 3:
            {
                total_amount += 10;
                break;
            }
            case 4:
            {
                total_amount += 25;
                break;
            }
            default:
            {
                coin_validator = false;
            }
            }
        }
        if (!coin_validator)
        {
            std::cout << "Sorry some of your coins were Invalid" << std::endl;
        }
        return total_amount;
    }

    static double enter_amount()
    {
        std::cout << "1. Penny (1 cent)" << std::endl;
        std::cout << "2. Nickel (5 cents)" << std::endl;
        std::cout << "3. Dime (10 cents)" << std::endl;
        std::cout << "4. Quarter (25 cents)" << std::endl;
        std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
        std::string coins;
        std::cout << "Enter your Coins : ";
        std::cin >> coins;
        return money_generator(coins);
    }
    static double return_total_money(User &user)
    {
        return user.get_user_balance() + cart_price(user);
    }
    static double cart_price(User &user)
    {
        double cartprice{};
        for (auto products : user.products)
        {
            cartprice += products.price;
        }
        return cartprice;
    }
    static void return_changes(User &user)
    {
        double balance = user.get_user_balance();
        if (balance > 0)
        {
            std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
            std::cout << "Please collect your balance of : $" << balance / 100 << std::endl;
            std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
            std::cout << std::setw(40) << std::setfill(' ') <<std::right<< (int)balance / 25 << "x 25 cents" << std::endl;
            balance = (int)balance % 25;
            std::cout << std::setw(40)<<std::right<< (int)balance / 10 << "x 10 cents" << std::endl;
            balance = (int)balance % 10;
            std::cout << std::setw(40) <<std::right<< (int)balance / 5 << "x 5 cents" << std::endl;
            balance = (int)balance % 5;
            std::cout << std::setw(40) <<std::right<< (int)balance / 1 << "x 1 cent" << std::endl;
        }

        std::cout << std::setw(75) << std::setfill('-') << "" << std::endl;
        std::cout << std::setw(48) << std::right << std::setfill(' ') << "...Thank you! come again..." << std::setw(49) << std::right << std::endl;
        std::cout << std::setw(75) << std::setfill('-') << "" << std::endl;
    }
};
#endif