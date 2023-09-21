#include <iostream>
#include <string>
#include <fstream>
#include "C:/sanjeev/codes/rapidjson/document.h"
#include "C:/sanjeev/codes/rapidjson/writer.h"
#include "C:/sanjeev/codes/rapidjson/stringbuffer.h"
#include "C:/sanjeev/codes/rapidjson/istreamwrapper.h"
#include "C:/sanjeev/codes/rapidjson/ostreamwrapper.h"
#include "jsonhandler.cpp"

struct login_credentials
{
    std::string user_id;
    std::string password;

    bool operator==(const login_credentials &rhs)
    {
        return (user_id == rhs.user_id && password == rhs.password);
    }
};

class Admin
{
private:
    login_credentials secret;
    JsonHandler json_handler;

public:
    static void admin_page()
    {
        std::string admin_name{};
        std::string admin_pass{};
        std::cout << "Enter user id : ";
        std::cin >> admin_name;
        std::cout << "Enter password : ";
        std::cin >> admin_pass;
        Admin adm;
        login_credentials admin_struct;
        admin_struct.user_id = admin_name;
        admin_struct.password = admin_pass;
        if (adm.Admin_verification(admin_struct))
        {
            bool admin_flag = true;
            while (admin_flag)
            {
                std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
                std::cout << "1. Add product " << std::endl;
                std::cout << "2. Modify supplies " << std::endl;
                std::cout << "3. Back " << std::endl;
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
                int admin_choice = std::stoi(str_choice);

                switch (admin_choice)
                {
                case 1:
                {
                    std::string name{};
                    std::string sprice{};
                    std::string squantity{};
                    int price{};
                    int quantity{};
                    std::cout << "Enter product name : ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    bool input_flag = true;
                    while (input_flag)
                    {
                        std::cout << "Enter product price : ";
                        std::cin >> sprice;
                        input_flag = false;
                        try
                        {
                            for (int i = 0; i < sprice.length(); i++)
                            {
                                if (std::isalpha(sprice[i]))
                                {

                                    input_flag = true;
                                    throw invalid_choice();
                                }
                            }
                        }
                        catch (std::runtime_error exp)
                        {
                            std::cout << exp.what() << std::endl;
                        }
                    }
                    price = std::stoi(sprice);
                    bool flag_quantity = true;
                    while (flag_quantity)
                    {
                        input_flag = true;
                        while (input_flag)
                        {
                            std::cout << "Enter product Quantity (MAX :10) : ";
                            std::cin >> squantity;
                            input_flag = false;
                            try
                            {
                                for (int i = 0; i < squantity.length(); i++)
                                {
                                    if (std::isalpha(squantity[i]))
                                    {
                                        input_flag = true;
                                        throw invalid_choice();
                                    }
                                }
                            }
                            catch (std::runtime_error exp)
                            {
                                std::cout << exp.what() << std::endl;
                            }
                        }
                        quantity = std::stoi(squantity);
                        if (quantity > 10)
                        {
                            quantity = 10;
                            std::cout << "Sorry Maximum limit reached..." << std::endl;
                            flag_quantity = false;
                        }
                        else if (quantity < 1)
                        {
                            std::cout << "Sorry Quantity must be greater than 0" << std::endl;
                            continue;
                        }
                        flag_quantity = false;
                    }
                    adm.Add_product(name, price, quantity);
                    std::cout << name << " added successfully..." << std::endl;
                    break;
                }
                case 2:
                {
                    std::string productid{};
                    bool input_flag = true;
                    std::string squantity{};
                    int quantity{};
                    std::cout << "Enter product id to modify : ";
                    std::cin >> productid;

                    bool flag_quantity = true;
                    while (flag_quantity)
                    {
                        input_flag = true;
                        while (input_flag)
                        {
                            std::cout << "Enter product Quantity (MAX :10) : ";

                            std::cin >> squantity;
                            input_flag = false;
                            try
                            {
                                for (int i = 0; i < squantity.length(); i++)
                                {
                                    if (std::isalpha(squantity[i]))
                                    {
                                        input_flag = true;
                                        throw invalid_input();
                                    }
                                }
                            }
                            catch (std::runtime_error exp)
                            {
                                std::cout << exp.what() << std::endl;
                            }
                        }
                        quantity = std::stoi(squantity);
                        if (quantity > 10)
                        {
                            quantity = 10;
                            std::cout << "Sorry Maximum limit reached..." << std::endl;
                            flag_quantity = false;
                        }
                        else if (quantity < 1)
                        {
                            std::cout << "Sorry Quantity must be greater than 0" << std::endl;
                            continue;
                        }
                        flag_quantity = false;
                    }

                    adm.Modify_Supplies(productid, quantity);
                    break;
                }
                case 3:
                {
                    admin_flag = false;
                    break;
                }
                }
            }
        }
    }
    bool Admin_verification(login_credentials user)
    {
        secret.user_id = "Admin";
        secret.password = "12345";
        return secret == user;
    }

    void Add_product(std::string name, int price, int quantity)
    {

        rapidjson::Document json_document = json_handler.Get_input_document();
        auto End_collection_pointer = json_document.End() - 1;
        std::string End_key = (*End_collection_pointer).MemberBegin()->name.GetString();
        int new_key = std::stoi(End_key) + 1;
        std::string str_new_key = std::to_string(new_key);
        auto key_to_add = rapidjson::StringRef((char *)str_new_key.c_str());
        auto name_to_add = rapidjson::StringRef((char *)name.c_str());

        rapidjson::Value Inner_collection(rapidjson::kObjectType);
        Inner_collection.AddMember("Name", name_to_add, json_document.GetAllocator());
        Inner_collection.AddMember("Price", price, json_document.GetAllocator());
        Inner_collection.AddMember("Quantity", quantity, json_document.GetAllocator());

        rapidjson::Value Collection_to_add(rapidjson::kObjectType);
        Collection_to_add.AddMember(key_to_add, Inner_collection, json_document.GetAllocator());

        json_document.GetArray().PushBack(Collection_to_add, json_document.GetAllocator());
        json_handler.Store_to_json(json_document);
    }

    void Modify_Supplies(std::string id, int quantity)
    {
        rapidjson::Document json_document = json_handler.Get_input_document();
        bool flag = false;
        for (auto array_iterator = json_document.Begin(); array_iterator != json_document.End(); array_iterator++)
        {

            std::string target_member = array_iterator->MemberBegin()->name.GetString();
            if (target_member == id)
            {
                auto value_to_modify = array_iterator->MemberBegin()->value.GetObject();
                rapidjson::Value &quantity_to_modify = value_to_modify["Quantity"];
                quantity_to_modify.SetInt(quantity);
                json_handler.Store_to_json(json_document);
                flag = true;
                break;
            }
        }
        if (flag)
        {
            std::cout << "Target value found and replaced" << std::endl;
        }
        else
        {
            std::cout << "Target value not found" << std::endl;
        }
    }
};