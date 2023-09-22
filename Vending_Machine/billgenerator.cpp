#ifndef _BILL__
#define _BILL__
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
class bill_generator
{

public:
    template <typename T>
    static void bill(std::vector<T> user_vector)
    {

        std::map<T, int> Map;
        for (auto product_iterator : user_vector)
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
        std::cout << std::setw(75) << std::setfill('_') << "" << std::endl;
        std::cout << std::setw(75) << std::setfill('-') << "" << std::endl;
        std::cout << std::setw(3) << std::left << std::setfill(' ') << "|";
        std::cout << std::setw(36) << std::right << std::setfill(' ') << "BILL" << std::setw(36) << std::right << "|" << std::endl;
        std::cout << std::setw(75) << std::setfill('-') << "" << std::endl<< std::endl;
        std::cout << std::setw(1) << std::left << std::setfill(' ') << "|";
        std::cout << std::setw(8) << std::right << "ID" << std::setw(6) << std::right << "|";
        std::cout << std::setw(9) << std::right << "Name" << std::setw(7) << std::right << "|";
        std::cout << std::setw(8) << std::right << "Price" << std::setw(6) << std::right << "|";
        std::cout << std::setw(10) << std::right << "Quantity" << std::setw(5) << std::right << "|";
        std::cout << std::setw(9) << std::right << "Total" << std::setw(6) << std::right << "|" << std::endl;
        std::cout << std::setw(75) << std::setfill('-') << "" << std::endl;
        double total_price = 0;
        for (auto map_iterator : Map)
        {
            total_price += (map_iterator.first.price * map_iterator.second);
            std::cout << std::endl;
            std::cout << std::setw(1) << std::left << std::setfill(' ') << "|";
            std::cout << std::setw(8) << std::right << (map_iterator).first.id << std::setw(6) << std::right << "|";
            std::cout << std::setw(10) << std::right << (map_iterator).first.name << std::setw(6) << std::right << "|";
            std::cout << std::setw(8) << (map_iterator).first.price << " c" << std::setw(4) << std::right << "|";
            std::cout << std::setw(7) << std::right << (map_iterator).second << std::setw(8) << std::right << "|";
            std::cout << std::setw(7) << (map_iterator).first.price * (map_iterator).second << " c" << std::setw(6) << std::right << "|";
            std::cout << std::endl;
        }

        std::cout << std::endl;
        std::cout << std::setw(75) << std::setfill('-') << "" << std::endl;
        std::cout << "|" << std::setw(35) << std::setfill(' ') << "TOTAL :" << std::setw(31) << "$ " << total_price / 100 << std::setw(6) << std::right << "|" << std::endl;
        std::cout << std::setw(75) << std::setfill('-') << "" << std::endl;
    }
};
#endif