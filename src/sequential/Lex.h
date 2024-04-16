#ifndef LEX_H
#define LEX_H

#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "../utils/DFA.h"
#include "../utils/Tokens.h"

class SeqLexer
{
public:
    std::string file;
    int index;
    Dlex dlex;
    SeqLexer(std::string file, Dlex dlex)
        : file(file), dlex(dlex) {
            this->index = 0;
        }
    std::vector<Token> getTokens()
    {
        this->index = 0;
        auto len = file.size();
        std::vector<Token> tokens;
        while (this->index < len)
        {
            Token token = getToken();
            tokens.push_back(token);
        }
        return tokens;
    }
    Token getToken()
    {
        std::optional<Token> last = std::optional<Token>();
        
        std::string current_string;
        int current_state = dlex.q1;
        auto len = file.size();
        while (true)
        {
            char ch = file.at(this->index);
            current_string += ch;
            int q = dlex.tau(current_state, ch);
            if (this->index + 1 == len)
            {
                index+=1;
                if (dlex.isFinal(q))
                    return Token(std::to_string(q), current_string);
                else
                    return Token("Invalid", "Invalid");
            }
            else if (dlex.isFinal(q))
            {
                this->index += 1;
                current_state = q;
                last = Token(std::to_string(q), current_string);
                last_ind = this->index;
            }
            else if (dlex.isInvalid(q))
            {
                this->index = last_ind;
                return last.value_or(Token("Invalid", "Invalid"));
            }
            else
            {
                this->index += 1;
                current_state = q;
            }
        }
    }
    private:
    int last_ind = 0;
};

#endif