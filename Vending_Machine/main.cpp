#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/istreamwrapper.h"
#include "../rapidjson/ostreamwrapper.h"
#include <iostream>
#include <fstream>
#include "Welcome_page.cpp"
#include "Menu_page.cpp"
#include "Admin.cpp"
using namespace rapidjson;

int main()
{
    std::shared_ptr<Document> document=std::make_shared<Document>(JsonHandler::Get_input_document());
    std::shared_ptr<User> user=std::make_shared<User>(User());
    Welcome_page::welcome(*document);
    int user_choice{};
    bool menu_flag = true;
    while (menu_flag)
    {
        user_choice = (Menu_page::general_menu());
        switch (user_choice)
        {
        case 1:
        {
            document=std::make_shared<Document>(JsonHandler::Get_input_document());
            Welcome_page::welcome(*document);
            break;
        }
        case 2:
        {
            (*user).set_user_balance((*user).get_user_balance() + Money_handler::enter_amount());
            Menu_page::user_menu(*user, *document);
            break;
        }
        case 3:
        {
            Admin::admin_page();
            break;
        }
        case 4:
        {
            
            Money_handler::return_changes(*user);
            menu_flag = false;
            break;
        }
        }
    }
}
