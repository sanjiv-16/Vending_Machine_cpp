#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include "jsonhandler.cpp"
#include "billgenerator.cpp"
#include "Choice_validator.cpp"
#include "Cart_page.cpp"
#include "Exception_handling.cpp"
JsonHandler jhandler;
using namespace rapidjson;
class Menu_page
{
public:
    static int general_menu()
    {
        std::cout << std::endl;
        std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
        std::cout << std::setw(3) << std::left << std::setfill(' ') << "|";
        std::cout << std::setw(48) << std::right << std::setfill(' ') << "MENU" << std::setw(49) << std::right << "|" << std::endl;
        std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
        std::cout << std::setw(30) << std::left << std::setfill(' ') << " " << std::setw(20) << "1. Display Products " << std::endl;
        std::cout << std::setw(30) << std::left << std::setfill(' ') << " " << std::setw(20) << "2. Enter Amount " << std::endl;
        std::cout << std::setw(30) << " " << std::setw(20) << "3. Admin Login " << std::endl;
        std::cout << std::setw(30) << " " << std::setw(20) << "4. Quit " << std::endl;
        std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
        std::string str_choice;
        while (true)
        {
            try
            {
                std::cout << "Please enter your choice : ";
                std::cin >> str_choice;
                if (Choice_validator::valid_choice(str_choice))
                {
                    break;
                }
                else
                    throw invalid_choice();
            }
            catch (std::runtime_error exp)
            {
                std::cout << exp.what() << std::endl;
            }
        }
        int choice = std::stoi(str_choice);
        while (choice > 4 || choice < 1)
        {
            std::cout << "Please enter a valid choice.. : ";
            std::cin >> choice;
        }
        return choice;
    }

    static void user_menu(User &user, Document &d)
    {
        bool menu_flag = true;
        int users_choice{};
        Welcome_page::welcome(d);
        while (menu_flag)
        {
            std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
            std::cout << "1. Display Products " << std::endl;
            std::cout << "2. Add product to cart " << std::endl;
            std::cout << "3. Go to cart " << std::endl;
            std::cout << "4. Add Extra amount " << std::endl;
            std::cout << "5. Cancel and Exit " << std::endl;
            std::cout << "6. Back" << std::endl;
            std::cout << " Your account balance is : $" << user.get_user_balance() / 100 << std::endl;
            std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
            std::string str_choice;
            while (true)
            {
                try
                {
                    std::cout << "Please enter your choice : ";
                    std::cin >> str_choice;
                    if (Choice_validator::valid_choice(str_choice))
                    {
                        break;
                    }
                    else
                        throw invalid_choice();
                }
                catch (std::runtime_error exp)
                {
                    std::cout << exp.what() << std::endl;
                }
            }
            int users_choice = std::stoi(str_choice);
            try
            {
                switch (users_choice)
                {
                case 1:
                {
                    d = JsonHandler::Get_input_document();
                    Welcome_page::welcome(d);
                    break;
                }
                case 2:
                {
                    Cart_page::user_add_product(user);
                    break;
                }
                case 3:
                {
                    if (Cart_page::cart_page(user))
                    {
                        Money_handler::return_changes(user);
                        user = User();
                        menu_flag = false;
                    }
                    break;
                }
                case 4:
                {
                    (user).set_user_balance((user).get_user_balance() + Money_handler::enter_amount());
                    std::cout << "Your account balance is : $" << user.get_user_balance() / 100 << std::endl;
                    break;
                }
                case 5:
                {
                    if (Cart_page::user_cancellation(user))
                    {
                        Money_handler::return_changes(user);
                        user = User();
                        menu_flag = false;
                    }
                    //menu_flag = false;
                    break;
                }
                case 6:
                {
                    menu_flag = false;
                    break;
                }
                default:
                {
                    throw invalid_choice();
                }
                }
            }
            catch (std::runtime_error exp)
            {
                std::cout << exp.what() << std::endl;
            }
        }
    }
};