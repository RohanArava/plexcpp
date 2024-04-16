#ifndef NPRESCAN_H
#define NPRESCAN_H

#include <string>
#include <vector>
#include <functional>
#include "../utils/DFA.h"

class NPrescan
{
public:
    std::vector<int> q;
    int q1;
    std::vector<int> alpha;
    std::vector<int> invalid;
    std::function<std::vector<int>(int, char)> tau;
    NPrescan(std::vector<int> q, int q1, std::vector<int> alpha, std::vector<int> invalid, std::function<std::vector<int>(int, char)> tau)
        : q(q), q1(q1), alpha(alpha), invalid(invalid), tau(tau) {}

    static NPrescan fromDlex(Dlex dlex){
        std::function<std::vector<int>(int, char)> _tau = [dlex](int st, char ch)->std::vector<int>{
            int next = dlex.tau(st, ch);
            std::vector<int> stv;
            if(dlex.isInvalid(next)){
                stv.push_back(dlex.tau(dlex.q1, ch));
            }else if(!dlex.isFinal(next)){
                stv.push_back(next);
                stv.push_back(dlex.tau(dlex.q1, ch));
            }else{
                stv.push_back(next);
            }
            return stv;
        };

        NPrescan nprescan = NPrescan(dlex.q, dlex.q1, dlex.alpha, dlex.invalid, _tau);
        return nprescan;
    }
    
    bool isFinal(int s)
    {
        for (int f : alpha)
        {
            if (f==s)
            {
                return true;
            }
        }
        return false;
    }
    bool isInvalid(int s)
    {
        for (int f : invalid)
        {
            if (f == s)
            {
                return true;
            }
        }
        return false;
    }
};

#endif