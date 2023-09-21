#include "C:/sanjeev/codes/rapidjson/document.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace rapidjson;

class Welcome_page
{
public:
    static void welcome(Document &d)
    {
        auto it = d.Begin();
        std::cout << std::setw(100) << std::setfill('_') << "" << std::endl;
        std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
        std::cout << std::setw(3) << std::left << std::setfill(' ') << "|";
        std::cout << std::setw(48) << std::right << std::setfill(' ') << "BEVERAGES" << std::setw(49) << std::right << "|" << std::endl;
        std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;

        auto it1 = (*it).MemberBegin();

        while (it != d.End())
        {
            it1 = (*it).MemberBegin();
            auto inner_member = (*it1).value.MemberBegin();

            std::cout << std::setw(1) << std::left << std::setfill(' ') << "|";
            std::cout << std::setw(33) << std::left << std::setfill(' ') << " " << std::setw(27) << std::setfill('-') << "-";
            std::cout << std::setw(39) << std::right << std::setfill(' ') << "|";
            std::cout << std::endl;
            std::cout << std::setw(1) << std::left << std::setfill(' ') << "|";
            std::cout << std::setw(34) << std::right << std::setfill(' ') << "|";
            std::cout << std::setw(12) << std::right << "ID : " << (*it1).name.GetString() << std::setw(11) << std::right << "|";
            std::cout << std::setw(39) << std::right << std::setfill(' ') << "|" << std::endl;
            std::cout << std::setw(1) << std::left << std::setfill(' ') << "|";
            std::cout << std::setw(34) << std::right << std::setfill(' ') << "|";
            std::cout << std::setw(15) << std::right << (*inner_member++).value.GetString() << std::setw(11) << std::right << "|";
            std::cout << std::setw(39) << std::right << std::setfill(' ') << "|" << std::endl;
            std::cout << std::setw(1) << std::left << std::setfill(' ') << "|";
            std::cout << std::setw(34) << std::right << std::setfill(' ') << "|";
            std::cout << std::setw(13) << std::right << (*inner_member++).value.GetInt() << " c" << std::setw(11) << std::right << "|";
            std::cout << std::setw(39) << std::right << std::setfill(' ') << "|" << std::endl;
            std::cout << std::setw(1) << std::left << std::setfill(' ') << "|";
            std::cout << std::setw(34) << std::right << std::setfill(' ') << "|";
            std::string price_string{""};
            if ((*inner_member).value.GetInt() < 10)
            {
                price_string = "0";
            }
            std::cout << std::setw(15) << std::right << (*inner_member).name.GetString() << " " << price_string << (*inner_member).value.GetInt() << std::setw(8) << std::right << "|";
            std::cout << std::setw(39) << std::right << std::setfill(' ') << "|" << std::endl;
            std::cout << std::setw(1) << std::left << std::setfill(' ') << "|";
            std::cout << std::setw(32) << std::left << std::setfill(' ') << " " << std::setw(28) << std::setfill('-') << " ";
            std::cout << std::setw(39) << std::right << std::setfill(' ') << "|" << std::endl;
            it++;
        }
        std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
    }
};