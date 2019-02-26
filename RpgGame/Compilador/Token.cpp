#include "Token.h"

bool Token::isTerminal()
{
    return false;
}

void Token::setId(int id)
{
    this->id = id;
}

void Token::setLexeme(string lexeme)
{
    this->lexeme = lexeme;
}

int Token::getId()
{
    return id;
}

string Token::getLexeme()
{
    return lexeme;
}
