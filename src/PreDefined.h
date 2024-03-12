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
    void basicExample()
    {
        State q_[] = {State("Start"), State("Int"), State("Q3"), State("Float"), State("Dot"), State("Ellipsis"), State("Invalid")};
        std::vector<State> q;
        for (int i = 0; i < 7; i++)
        {
            q.push_back(q_[i]);
        }

        State alpha_[] = {State("Int"), State("Float"), State("Dot"), State("Ellipsis")};
        std::vector<State> alpha;
        for (int i = 0; i < 4; i++)
        {
            alpha.push_back(alpha_[i]);
        }

        std::vector<State> invalid;
        invalid.push_back(State("Invalid"));
        Dlex dlex = Dlex(
            q, State("Start"), alpha, invalid,
            [](State state, char ch) -> State
            {
            std::string str = state.name;
            if(str.compare("Start")==0){
                if (ch=='.') return State("Dot");
                else return State("Int");
            } else if(str.compare("Int")==0){
                if (ch=='.') return State("Q3");
                else return State("Int");
            } else if(str.compare("Q3")==0){
                if (ch=='.') return State("Invalid");
                else return State("Float");
            } else if(str.compare("Float")==0){
                if (ch=='.') return State("Invalid");
                else return State("Float");
            } else if(str.compare("Dot")==0){
                if (ch=='.') return State("Ellipsis");
                else return State("Invalid");
            } else if(str.compare("Ellipsis")==0){
                return State("Invalid");
            } else return State("Invalid"); }
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
        State q_[] = {State("Start"), State("Int"), State("Q1"), State("Float"), State("UnQuotedString"), State("QuotedString"), State("QuotedStringEnd"), State("Invalid"), State("Delim")};
        std::vector<State> q;
        for (int i = 0; i < 9; i++)
        {
            q.push_back(q_[i]);
        }

        State alpha_[] = {State("Int"), State("Float"), State("Q1"), State("UnQuotedString"), State("QuotedStringEnd"), State("Delim")};
        std::vector<State> alpha;
        for (int i = 0; i < 6; i++)
        {
            alpha.push_back(alpha_[i]);
        }

        std::vector<State> invalid;
        invalid.push_back(State("Invalid"));

        Dlex dlex = Dlex(
            q, State("Start"), alpha, invalid, [](State state, char ch) -> State
            {
            std::string str = state.name;
            if(str.compare("Start")==0){
                if(ch==',' || ch=='\n') return State("Delim");
                else if(ch=='"') return State("QuotedString");
                else if(isdigit(ch) || ch=='-') return State("Int");
                else return State("UnQuotedString");
            } else if(str.compare("Int")==0){
                if(ch==',' || ch=='\n') return State("Invalid");
                else if(isdigit(ch)) return State("Int");
                else if(ch=='.') return State("Q1");
                else return State("UnQuotedString");
            } else if(str.compare("Q1")==0){
                if(ch==',' || ch=='\n') return State("Invalid");
                else if(isdigit(ch)) return State("Float");
                else return State("UnQuotedString");
            } else if(str.compare("Float")==0){
                if(ch==',' || ch=='\n') return State("Invalid");
                else if(isdigit(ch)) return State("Float");
                else return State("UnQuotedString");
            } else if(str.compare("UnQuotedString")==0){
                if(ch==',' || ch=='\n') return State("Invalid");
                else return State("UnQuotedString");
            } else if(str.compare("QuotedString")==0){
                if (ch=='"') return State("QuotedStringEnd");
                else return State("QuotedString");
            } else if(str.compare("QuotedStringEnd")==0){
                if(ch==',' || ch=='\n') return State("Invalid");
                else return State("UnQuotedString");
            } else if(str.compare("Delim")==0){
                if(ch == ' ') return State("Delim");
                else return State("Invalid");
            } else return State("Invalid"); });
        SeqLexer lexer = SeqLexer(file, dlex);
        // std::cout << file << std::endl;
        auto tokens = lexer.getTokens();
        std::cout << tokens.size() << std::endl;
        // for (auto token : tokens)
        // {
        //     std::cout << token.to_string() << ",";
        // }
        // std::cout << std::endl;
    }
};

#endif