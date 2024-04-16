#ifndef DPRESCAN_H
#define DPRESCAN_H

#include <vector>
#include <map>
#include <climits>
#include <cstdlib>
#include "../utils/DFA.h"
#include "NPrescan.h"
class DPrescan
{
public:
    std::vector<std::vector<int>> q;
    int q1;
    std::vector<std::vector<int>> alpha;
    std::map<std::vector<int>, std::map<char, std::vector<int>>> tau;
    DPrescan(std::vector<std::vector<int>> q, int q1, std::vector<std::vector<int>> alpha, std::map<std::vector<int>, std::map<char, std::vector<int>>> tau)
        : q(q), q1(q1), alpha(alpha), tau(tau) {}
    static DPrescan construct(Dlex dlex)
    {
        NPrescan nprescan = NPrescan::fromDlex(dlex);
        std::vector<std::vector<int>> q_;
        std::vector<std::vector<int>> q_tmp({{dlex.q1}});
        std::map<std::vector<int>, std::map<char, std::vector<int>>> tau_;
        std::vector<std::vector<int>> alpha_;
        while (!q_tmp.empty())
        {
            // std::cout << q_tmp.size() << std::endl;
            // for (auto q : q_)
            // {
            //     std::cout << "vec : ";
            //     for (auto i : q)
            //     {
            //         std::cout << i << " ";
            //     }
            //     std::cout << std::endl;
            // }
            // int r = rand() % q_tmp.size();
            int r = q_tmp.size() -1;
            std::vector<int> S = q_tmp[r];
            q_tmp.erase(std::next(q_tmp.begin(), r));
            q_.push_back(S);
            for (char c = CHAR_MIN; c < CHAR_MAX; c++)
            {
                std::vector<int> O;
                for (int n = 0; n < S.size(); n++)
                {
                    int st = dlex.tau(S[n], c);
                    if (!int_is_in_O(O, st))
                    {
                        if (!dlex.isInvalid(st))
                            O.push_back(st);
                    }
                    std::vector<int> st_n = nprescan.tau(S[n], c);
                    for (int i = 0; i < st_n.size(); i++)
                    {
                        if (!int_is_in_O(O, st_n[i]) && !dlex.isInvalid(st_n[i]))
                        {
                            O.push_back(st_n[i]);
                        }
                    }
                    if (dlex.isFinal(O[O.size() - 1]))
                    {
                        O.push_back(dlex.q1);
                        break;
                    }
                    
                }
                // std::cout << "O : ";
                //     for (auto i : O)
                //     {
                //         std::cout << i << " ";
                //     }
                //     std::cout << std::endl;
                if (!vec_is_in_vec_of_vecs(O, q_tmp) && !vec_is_in_vec_of_vecs(O, q_))
                {
                    // std::cout << "push O" << std::endl;
                    q_tmp.push_back(O);
                }
                for (int i = 0; i < O.size(); i++)
                {
                    if (dlex.isFinal(O[i]))
                    {
                        alpha_.push_back(O);
                        break;
                    }
                }
                if (tau_.find(S) != tau_.end())
                {
                    auto t = tau_[S];
                    t.insert_or_assign(c, O);
                }
            }
        }
        std::cout << q_.size() << std::endl;
        for (auto q : q_)
            {
                std::cout << "vec : ";
                for (auto i : q)
                {
                    std::cout << i << " ";
                }
                std::cout << std::endl;
            }
        return DPrescan(q_, dlex.q1, alpha_, tau_);
    }

    bool isFinal(std::vector<int> O)
    {
        for (int i = 0; i < alpha.size(); i++)
        {
            if (O == alpha[i])
            {
                return true;
            }
        }
        return false;
    }
    static bool are_vecs_equal(std::vector<int> v1, std::vector<int> v2)
    {
        if (v1.size() != v2.size())
            return false;
        for (int i = 0; i < v1.size(); i++)
        {
            if (v1[i] != v2[i])
                return false;
        }
        return true;
    }
    static bool vec_is_in_vec_of_vecs(std::vector<int> v, std::vector<std::vector<int>> vv)
    {
        for (auto v_ : vv)
        {
            if (are_vecs_equal(v, v_))
                return true;
        }
        return false;
    }

    static bool int_is_in_O(std::vector<int> O, int n)
    {
        for (int i = 0; i < O.size(); i++)
        {
            if (n == O[i])
                return true;
        }
        return false;
    }
};

#endif