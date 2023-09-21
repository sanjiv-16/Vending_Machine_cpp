#include "C:/sanjeev/codes/rapidjson/document.h"
#include "C:/sanjeev/codes/rapidjson/writer.h"
#include "C:/sanjeev/codes/rapidjson/stringbuffer.h"
#include "C:/sanjeev/codes/rapidjson/istreamwrapper.h"
#include "C:/sanjeev/codes/rapidjson/ostreamwrapper.h"
#include <iostream>
#include <fstream>
#include "Welcome_page.cpp"
#include "Menu_page.cpp"
#include "Admin.cpp"
using namespace rapidjson;

int main()
{
    Document d = JsonHandler::Get_input_document();
    Welcome_page::welcome(d);
    int user_choice{};
    bool menu_flag = true;
    User user = (User());
    while (menu_flag)
    {
        user_choice = (Menu_page::general_menu());
        switch (user_choice)
        {
        case 1:
        {
            d = JsonHandler::Get_input_document();
            Welcome_page::welcome(d);
            break;
        }
        case 2:
        {
            (user).set_user_balance((user).get_user_balance() + Money_handler::enter_amount());
            Menu_page::user_menu(user, d);
            break;
        }
        case 3:
        {
            Admin::admin_page();
            break;
        }
        case 4:
        {
            std::cout << "Thank you" << std::endl;
            menu_flag = false;
            break;
        }
        }
    }
}