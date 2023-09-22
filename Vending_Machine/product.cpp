#ifndef _PRODUCT__
#define _PRODUCT__
#include <string>
#include <iostream>
class Product
{
    friend std::ostream &operator<<(std::ostream &out, Product product)
    {
        out << product.id << ". " << product.name << " - " << product.price << " c";
        return out;
    }

public:
    std::string id{};
    std::string name{};
    int price{};
    int quantity{};
    Product() = default;
    Product(std::string id, std::string name, int price, int quantity)
    {
        this->id = id;
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }
    int get_price()
    {
        return price;
    }
    bool operator==(const Product &rhs) const
    {
        return (id == rhs.id);
    }

    bool operator<(const Product &rhs) const
    {
        return (id < rhs.id);
    }
};
#endif