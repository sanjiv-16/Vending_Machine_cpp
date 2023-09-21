#include "User.cpp"
#include "product.cpp"
#include <iomanip>
#include <map>
#include "Money_handler.cpp"
#include "Choice_validator.cpp"
#include "Exception_handling.cpp"
#include "billgenerator.cpp"
#include "jsonhandler.cpp"
#include <algorithm>
JsonHandler jshandler;
class Cart_page
{
public:
    static void user_add_product(User &user)
    {
        std::string product_id;
        std::cout << "Enter your product id :";
        std::cin >> product_id;
        try
        {
            if (jshandler.contains(product_id))
            {
                if (jshandler.supply_manager(product_id, -1))
                {
                    if (user.get_user_balance() - jshandler.find<Product>(product_id).price >= 0)
                    {
                        user.set_user_balance(user.get_user_balance() - jshandler.find<Product>(product_id).price);
                        user.products.push_back(jshandler.find<Product>(product_id));
                    }
                    else
                        throw insufficient_balance();
                }
                else
                    throw insufficient_product();
            }
            else
                throw invalid_product();
        }
        catch (std::runtime_error exp)
        {
            std::cout << exp.what() << std::endl;
        }
    }
    static bool user_cancellation(User &user)
    {
        bool flag = true;
        while (flag)
        {
            try
            {
                std::cout << "Are you sure to Cancel (Y/N) : ";
                std::string strchoice;
                std::cin >> strchoice;
                char choice = strchoice[0];
                choice = tolower(choice);
                if (choice == 'y')
                {
                    for (auto products : user.products)
                    {
                        jshandler.supply_manager(products.id, 1);
                    }
                    user.set_user_balance(Money_handler::return_total_money(user));
                    return true;
                }
                else if (choice == 'n')
                {
                    flag=false;
                }
                else
                {
                    throw invalid_choice();
                }
            }
            catch (std::runtime_error exp)
            {
                std::cout << exp.what() << std::endl;
            }
        }
        return false;
    }
    static bool delete_user_product(User &user)
    {
        std::string productid{};
        std::cout << "Enter the product id : ";
        std::cin >> productid;
        auto it = find(user.products.begin(), user.products.end(), jshandler.find<Product>(productid));
        if (it == user.products.end())
        {
            return false;
        }
        jshandler.supply_manager((*it).id, 1);
        user.set_user_balance(user.get_user_balance() + (*it).get_price());
        std::cout << (*it).name << " Deleted" << std::endl;
        user.products.erase(it);
        return true;
    }
    static bool cart_page(User &user)
    {
        bool completion_status = false;
        std::map<Product, int> Map;
        for (auto product_iterator : user.products)
        {
            if (Map.count(product_iterator) > 0)
            {
                Map[product_iterator] = Map.at(product_iterator) + 1;
            }
            else
            {
                Map[product_iterator] = 1;
            }
        }
        std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
        std::cout << std::setw(30) << std::setfill(' ') << "Your Cart" << std::endl;
        std::cout << std::setw(100) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
        for (auto i : Map)
            std::cout << std::setw(20) << i.first << "   x" << i.second << std::endl;
        std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
        bool cart_flag = true;
        while (cart_flag)
        {
            std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
            std::cout << std::setw(20) << std::left << std::setfill(' ') << "1. Buy now " << std::endl;
            std::cout << std::setw(20) << std::setfill(' ') << "2. Delete product " << std::endl;
            std::cout << std::setw(20) << std::setfill(' ') << "3. Back " << std::endl;
            std::cout << std::setw(100) << std::setfill('-') << "" << std::setfill(' ') << std::endl;
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
            int cartchoice = std::stoi(str_choice);
            try
            {
                switch (cartchoice)
                {
                case 1:
                {
                    if (user.products.empty())
                    {
                        std::cout << "            Your cart is Empty... " << std::endl;
                        bool quit_flag = true;
                        while (quit_flag)
                        {
                            try
                            {
                                std::cout << "Are you sure to quit (Y/N) : ";
                                std::string quit_choice{};
                                std::cin >> quit_choice;
                                char choice = quit_choice[0];
                                choice = tolower(choice);
                                if (choice == 'y')
                                {
                                    cart_flag = false;
                                    quit_flag = false;
                                    completion_status = true;
                                }
                                else if (choice == 'n')
                                {
                                    quit_flag = false;
                                    cart_flag=false;
                                }
                                else
                                {
                                    throw invalid_choice();
                                }
                            }
                            catch (std::runtime_error exp)
                            {
                                std::cout << exp.what() << std::endl;
                            }
                        }
                    }
                    else
                    {
                        bill_generator::bill(user.products);
                        cart_flag = false;
                        completion_status = true;
                        break;
                    }
                    break;
                }
                case 2:
                {
                    if (!delete_user_product(user))
                    {
                        throw invalid_product();
                    }
                    break;
                }
                case 3:
                {
                    cart_flag = false;
                    break;
                }
                default:
                    throw invalid_choice();
                }
            }
            catch (std::runtime_error exp)
            {
                std::cout << exp.what() << std::endl;
            }
        }
        return completion_status;
    }
};
