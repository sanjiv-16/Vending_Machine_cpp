#ifndef _JSON__
#define _JSON__
#include <iostream>
#include <string>
#include <fstream>
#include "C:/sanjeev/codes/rapidjson/document.h"
#include "C:/sanjeev/codes/rapidjson/writer.h"
#include "C:/sanjeev/codes/rapidjson/stringbuffer.h"
#include "C:/sanjeev/codes/rapidjson/istreamwrapper.h"
#include "C:/sanjeev/codes/rapidjson/ostreamwrapper.h"
// #include "product.cpp"

class JsonHandler
{
public:
    static rapidjson::Document Get_input_document()
    {
        rapidjson::Document json_document;
        std::ifstream input_file{"Vending_library.json"};

        if (!input_file)
        {
            std::cout << "Error in opening json file" << std::endl;
        }

        rapidjson::IStreamWrapper Input_Stream_Wrapper(input_file);
        json_document.ParseStream(Input_Stream_Wrapper);
        return json_document;
    }

    void Store_to_json(rapidjson::Document &json_document)
    {
        std::ofstream output_file{"Vending_library.json"};
        if (!output_file)
        {
            std::cout << "Error in opening json file" << std::endl;
        }
        rapidjson::OStreamWrapper Output_stream_wrapper(output_file);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(Output_stream_wrapper);
        json_document.Accept(writer);
    }
    template <typename T>
    T find(std::string id)
    {
        rapidjson::Document jsonDocument = Get_input_document();
        for (auto array_iterator = jsonDocument.Begin(); array_iterator != jsonDocument.End(); array_iterator++)
        {
            std::string target_member = array_iterator->MemberBegin()->name.GetString();
            if (target_member == id)
            {
                auto get_value = array_iterator->MemberBegin()->value.GetObject();
                int quantity = get_value["Quantity"].GetInt();
                std::string name = get_value["Name"].GetString();
                int price = get_value["Price"].GetInt();
                return T(id, name, price, quantity);
            }
        }
        return T();
    }

    bool contains(std::string id)
    {
        rapidjson::Document jsonDocument = Get_input_document();
        bool flag = false;
        for (auto array_iterator = jsonDocument.Begin(); array_iterator != jsonDocument.End(); array_iterator++)
        {
            std::string target_member = array_iterator->MemberBegin()->name.GetString();
            if (target_member == id)
            {
                return true;
            }
        }
        return false;
    }

    bool supply_manager(std::string id, int quantity)
    {
        rapidjson::Document json_document = Get_input_document();

        for (auto array_iterator = json_document.Begin(); array_iterator != json_document.End(); array_iterator++)
        {
            std::string target_member = array_iterator->MemberBegin()->name.GetString();
            if (target_member == id)
            {
                auto value_to_modify = array_iterator->MemberBegin()->value.GetObject();
                rapidjson::Value &quantity_to_modify = value_to_modify["Quantity"];
                if (quantity_to_modify.GetInt() + (quantity) >= 0)
                {
                    quantity_to_modify.SetInt(quantity_to_modify.GetInt() + (quantity));
                    Store_to_json(json_document);
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        return false;
    }
};
#endif