#ifndef DFA_H
#define DFA_H

#include <string>
#include <vector>
#include <functional>
class State
{
public:
    std::string name;
    State(std::string name) : name(name) {}
    bool operator==(State s)
    {
        return this->name == s.name;
    }
    std::string to_string()
    {
        return "State(" + this->name + ")";
    }
};

class Dlex
{
public:
    std::vector<State> q;
    State q1;
    std::vector<State> alpha;
    std::vector<State> invalid;
    std::function<State(State, char)> tau;
    Dlex(std::vector<State> q, State q1, std::vector<State> alpha, std::vector<State> invalid, std::function<State(State, char)> tau)
        : q(q), q1(q1), alpha(alpha), invalid(invalid), tau(tau) {}

    // State getTau(State stv, char chv){
    //     for(auto tp : tau){
    //         if(std::get<0>(tp).name.compare(stv.name)==0 && std::get<1>(tp) == chv){
    //             return std::get<2>(tp);
    //         }
    //     }
    //     return invalid.at(0);
    // }
    bool isFinal(State s)
    {
        for (State f : alpha)
        {
            if (f.name.compare(s.name) == 0)
            {
                return true;
            }
        }
        return false;
    }
    bool isInvalid(State s)
    {
        for (State f : invalid)
        {
            if (f.name.compare(s.name) == 0)
            {
                return true;
            }
        }
        return false;
    }
};

#endif