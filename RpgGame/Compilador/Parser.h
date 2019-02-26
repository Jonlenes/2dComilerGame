#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"
#include "Grammar/GrammarLL.h"
#include "Compilador/Enums.h"

#include <iostream>
#include <vector>

using namespace std;

class Parser
{
public:
    Parser(string source);

    bool execute();
    vector<Token *> getTokens();
    vector<string> getErrors();

private:
    string source;
    GrammarLL grammarLL;
    Scanner scanner;
    vector<string> listErrors;
    vector<Token *> tokens;

    void monthsGrammarCompiler();
    void addError(int index, Token *token = nullptr, int id = -1);
};

#endif // PARSER_H
