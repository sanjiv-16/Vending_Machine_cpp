#ifndef _CHOICE__
#define _CHOICE__
#include <string>
class Choice_validator
{
    public:
    static bool valid_choice(std::string strinput)
    {
        return(!(strinput.length()>1 || (std::isalpha(strinput[0]))));
    }
};
#endif