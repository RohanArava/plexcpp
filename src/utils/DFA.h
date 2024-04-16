#ifndef DFA_H
#define DFA_H

#include <string>
#include <vector>
#include <functional>
// class int
// {
// public:
//     std::string name;
//     int(std::string name) : name(name) {}
//     bool operator==(int s)
//     {
//         return this->name == s.name;
//     }
//     std::string to_string()
//     {
//         return "int(" + this->name + ")";
//     }
// };

class Dlex
{
public:
    std::vector<int> q;
    int q1;
    std::vector<int> alpha;
    std::vector<int> invalid;
    std::function<int(int, char)> tau;
    Dlex(std::vector<int> q, int q1, std::vector<int> alpha, std::vector<int> invalid, std::function<int(int, char)> tau)
        : q(q), q1(q1), alpha(alpha), invalid(invalid), tau(tau) {}

    // int getTau(int stv, char chv){
    //     for(auto tp : tau){
    //         if(std::get<0>(tp).name.compare(stv.name)==0 && std::get<1>(tp) == chv){
    //             return std::get<2>(tp);
    //         }
    //     }
    //     return invalid.at(0);
    // }
    bool isFinal (int s) const
    {
        for (int f : alpha)
        {
            if (s==f)
            {
                return true;
            }
        }
        return false;
    }
    bool isInvalid (int s) const
    {
        for (int f : invalid)
        {
            if (s==f)
            {
                return true;
            }
        }
        return false;
    }
};

#endif