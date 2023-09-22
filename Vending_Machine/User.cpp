#ifndef _USER__
#define _USER__
#include <iostream>
#include <vector>
#include "product.cpp"
class User
{
private:
    double user_balance{};
    User(){};

public:
    
    std::vector<Product> products;
    static User create_user(){
        return User();
    }
    double get_user_balance() { return user_balance; }
    void set_user_balance(double balance) { user_balance = balance; }
    void set_to_default(){
        user_balance=0;
    }
    
};
#endif