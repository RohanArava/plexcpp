#ifndef NPRESCAN_H
#define NPRESCAN_H

#include <string>
#include <vector>
#include <functional>
#include "../utils/DFA.h"

class NPrescan
{
public:
    std::vector<State> q;
    State q1;
    std::vector<State> alpha;
    std::vector<State> invalid;
    std::function<std::vector<State>(State, char)> tau;
    NPrescan(std::vector<State> q, State q1, std::vector<State> alpha, std::vector<State> invalid, std::function<std::vector<State>(State, char)> tau)
        : q(q), q1(q1), alpha(alpha), invalid(invalid), tau(tau) {}

    static NPrescan fromDlex(Dlex dlex){
        std::function<std::vector<State>(State, char)> _tau = [dlex](State st, char ch)->std::vector<State>{
            std::vector<State> stv;
            stv.push_back(dlex.tau(st, ch));
            return stv;
        };
        
    }
    
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