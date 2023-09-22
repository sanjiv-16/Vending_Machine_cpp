#ifndef _USER__
#define _USER__
#include <iostream>
#include <vector>
#include "product.cpp"
class User
{
private:
    double user_balance{};

public:
    std::vector<Product> products;
    User(){};
    User(double entered_amount) { user_balance = entered_amount; }
    double get_user_balance() { return user_balance; }
    void set_user_balance(double balance) { user_balance = balance; }
    
};
#endif