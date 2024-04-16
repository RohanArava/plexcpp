#ifndef TOKENS_H
#define TOKENS_H

#include<string>

class Token{
    public:
    std::string type;
    std::string value;
    Token(std::string type, std::string value): type(type), value(value) {}
    std::string to_string(){
        return "(\"" + type + "\": \"" + value + "\")";
    }
};

#endif