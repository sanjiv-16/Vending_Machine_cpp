#include<iostream>
#ifndef _EXCEPTION__
#define _EXCEPTION__
class insufficient_balance:public std::runtime_error{
     public:
    insufficient_balance():std::runtime_error{"Sorry insuffitient balance...."}{

    }
};
class insufficient_product:public std::runtime_error{
     public:
    insufficient_product():std::runtime_error{"Sorry insuffitient product...."}{

    }
};
class invalid_product:public std::runtime_error{
     public:
    invalid_product():std::runtime_error{"Sorry invalid product...."}{

    }
};
class invalid_choice:public std::runtime_error{
     public:
    invalid_choice():std::runtime_error{"Sorry invalid choice...."}{

    }
};
class invalid_input:public std::runtime_error{
     public:
    invalid_input():std::runtime_error{"Sorry invalid input...."}{

    }
};
#endif