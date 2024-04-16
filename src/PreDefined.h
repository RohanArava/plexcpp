#ifndef PREDEFINED_H
#define PREDEFINED_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "./utils/DFA.h"
#include "./utils/Tokens.h"
#include "./sequential/Lex.h"

class PreDefined
{
public:

    Dlex example_dlex(){
        int q_[] = {0, 1, 2, 3, 4, 5, 6};
        std::vector<int> q;
        for (int i = 0; i < 7; i++)
        {
            q.push_back(q_[i]);
        }

        int alpha_[] = {1, 3, 4, 5};
        std::vector<int> alpha;
        for (int i = 0; i < 4; i++)
        {
            alpha.push_back(alpha_[i]);
        }

        std::vector<int> invalid;
        invalid.push_back(6);
        Dlex dlex = Dlex(
            q, 0, alpha, invalid,
            [](int state, char ch) -> int
            {
            if(state == 0){
                if (ch=='.') return 4;
                else return 1;
            } else if(state == 1){
                if (ch=='.') return 2;
                else return 1;
            } else if(state == 2){
                if (ch=='.') return 6;
                else return 3;
            } else if(state == 3){
                if (ch=='.') return 6;
                else return 3;
            } else if(state == 4){
                if (ch=='.') return 5;
                else return 6;
            } else if(state == 5){
                return 6;
            } else return 6; }
            );
        return dlex;
    }
    void basicExample()
    {
        int q_[] = {0, 1, 2, 3, 4, 5, 6};
        std::vector<int> q;
        for (int i = 0; i < 7; i++)
        {
            q.push_back(q_[i]);
        }

        int alpha_[] = {1, 3, 4, 5};
        std::vector<int> alpha;
        for (int i = 0; i < 4; i++)
        {
            alpha.push_back(alpha_[i]);
        }

        std::vector<int> invalid;
        invalid.push_back(6);
        Dlex dlex = Dlex(
            q, 0, alpha, invalid,
            [](int state, char ch) -> int
            {
            if(state == 0){
                if (ch=='.') return 4;
                else return 1;
            } else if(state == 1){
                if (ch=='.') return 2;
                else return 1;
            } else if(state == 2){
                if (ch=='.') return 6;
                else return 3;
            } else if(state == 3){
                if (ch=='.') return 6;
                else return 3;
            } else if(state == 4){
                if (ch=='.') return 5;
                else return 6;
            } else if(state == 5){
                return 6;
            } else return 6; }
            );
        SeqLexer lexer = SeqLexer("10.789", dlex);
        auto tokens = lexer.getTokens();
        std::cout << tokens.size() << std::endl;
        for (auto token : tokens)
        {
            std::cout << token.to_string() << ",";
        }
        std::cout << std::endl;
    }

    Dlex csv_dlex(){
        int q_[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        std::vector<int> q;
        for (int i = 0; i < 9; i++)
        {
            q.push_back(q_[i]);
        }

        int alpha_[] = {1, 3, 2, 4, 6, 8};
        std::vector<int> alpha;
        for (int i = 0; i < 6; i++)
        {
            alpha.push_back(alpha_[i]);
        }

        std::vector<int> invalid;
        invalid.push_back(7);

        Dlex dlex = Dlex(
            q, 0, alpha, invalid, [](int state, char ch) -> int
            {
            if(state==0){
                if(ch==',' || ch=='\n') return 8;
                else if(ch=='"') return 5;
                else if(isdigit(ch) || ch=='-') return 1;
                else return 4;
            } else if(state==1){
                if(ch==',' || ch=='\n') return 7;
                else if(isdigit(ch)) return 1;
                else if(ch=='.') return 2;
                else return 4;
            } else if(state==2){
                if(ch==',' || ch=='\n') return 7;
                else if(isdigit(ch)) return 3;
                else return 4;
            } else if(state==3){
                if(ch==',' || ch=='\n') return 7;
                else if(isdigit(ch)) return 3;
                else return 4;
            } else if(state==4){
                if(ch==',' || ch=='\n') return 7;
                else return 4;
            } else if(state==5){
                if (ch=='"') return 6;
                else return 5;
            } else if(state==6){
                if(ch==',' || ch=='\n') return 7;
                else return 4;
            } else if(state==8){
                if(ch == ' ') return 8;
                else return 7;
            } else return 7; });
        return dlex;
    }

    void CSV(std::string filename)
    {
        std::ifstream f(filename);
        std::string file;
        if (f)
        {
            std::ostringstream ss;
            ss << f.rdbuf();
            file = ss.str();
        }
        int q_[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        std::vector<int> q;
        for (int i = 0; i < 9; i++)
        {
            q.push_back(q_[i]);
        }

        int alpha_[] = {1, 3, 2, 4, 6, 8};
        std::vector<int> alpha;
        for (int i = 0; i < 6; i++)
        {
            alpha.push_back(alpha_[i]);
        }

        std::vector<int> invalid;
        invalid.push_back(7);

        Dlex dlex = Dlex(
            q, 0, alpha, invalid, [](int state, char ch) -> int
            {
            if(state==0){
                if(ch==',' || ch=='\n') return 8;
                else if(ch=='"') return 5;
                else if(isdigit(ch) || ch=='-') return 1;
                else return 4;
            } else if(state==1){
                if(ch==',' || ch=='\n') return 7;
                else if(isdigit(ch)) return 1;
                else if(ch=='.') return 2;
                else return 4;
            } else if(state==2){
                if(ch==',' || ch=='\n') return 7;
                else if(isdigit(ch)) return 3;
                else return 4;
            } else if(state==3){
                if(ch==',' || ch=='\n') return 7;
                else if(isdigit(ch)) return 3;
                else return 4;
            } else if(state==4){
                if(ch==',' || ch=='\n') return 7;
                else return 4;
            } else if(state==5){
                if (ch=='"') return 6;
                else return 5;
            } else if(state==6){
                if(ch==',' || ch=='\n') return 7;
                else return 4;
            } else if(state==8){
                if(ch == ' ') return 8;
                else return 7;
            } else return 7; });
        SeqLexer lexer = SeqLexer(file, dlex);
        // std::cout << file << std::endl;
        auto tokens = lexer.getTokens();
        std::cout << tokens.size() << std::endl;
        // for (auto token : tokens)
        // {
        //     std::cout << "token: " << std::endl << token.to_string() << std::endl;
        // }
        std::cout << std::endl;
    }
};

#endif