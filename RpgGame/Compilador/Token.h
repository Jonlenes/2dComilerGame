#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

#include "Grammar/GrammarElement.h"

using namespace std;

// Criado por: Jonlenes
// Data: 12/03/2016 18:35

class Token : public GrammarElement
{
public:
    Token();
    Token(int id) : id(id) {}
    Token(string lexeme) : lexeme(lexeme) {}
    Token(int id, string lexeme)
        : id(id), lexeme(lexeme) {}
    ~Token() {}

    bool isTerminal() override final;
    void setId(int id);
    void setLexeme(string lexeme) ;
    int getId() override final;
    string getLexeme();


private:
    int id;
    string lexeme;
};

#endif // TOKEN_H
