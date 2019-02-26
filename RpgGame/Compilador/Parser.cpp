#include "Parser.h"

#include <stack>

Parser::Parser(string source)
{
    scanner.setSource(source);
    monthsGrammarCompiler();
}

bool Parser::execute()
{
    Token *token;
    stack<int> stackS;
    Production *production;
    int idGrammarElement;


    token = scanner.nextToken();
    stackS.push(grammarLL.getIdProduction("INI"));

    while (true) {
        if (stackS.empty()) return (!token);

        idGrammarElement = stackS.top();
        stackS.pop();

        if (grammarLL.isTerminal(idGrammarElement)) {
            token? production = grammarLL.getProduction(grammarLL.getProductionName(idGrammarElement), token->getId()) : production = nullptr;
            if (production) {
                for (int i = production->getListElements()->size() - 1; i >= 0; --i) {
                    stackS.push((*production->getListElements())[i]);
                }
            } else if (!grammarLL.getProduction(grammarLL.getProductionName(idGrammarElement), Epsilon)) return false;
        } else if (token && token->getId() == idGrammarElement) {
            tokens.push_back(token);
            token = scanner.nextToken();
        } else return false;
    }

    return false;
}

 vector<Token *> Parser::getTokens()
{
    return tokens;
}

vector<string> Parser::getErrors()
{
    return listErrors;
}

void Parser::monthsGrammarCompiler()
{
    grammarLL.addProduction(new Production("INI", { A, grammarLL.getIdProduction("INI")}));
    grammarLL.addProduction(new Production("INI", { D, grammarLL.getIdProduction("INI")}));
    grammarLL.addProduction(new Production("INI", { S, grammarLL.getIdProduction("INI")}));
    grammarLL.addProduction(new Production("INI", { M, Integer, grammarLL.getIdProduction("MOVE")}));
    grammarLL.addProduction(new Production("MOVE", { L, grammarLL.getIdProduction("INI")}));
    grammarLL.addProduction(new Production("MOVE", { R, grammarLL.getIdProduction("INI")}));
    grammarLL.addProduction(new Production("MOVE", { U, grammarLL.getIdProduction("INI")}));
    grammarLL.addProduction(new Production("MOVE", { D, grammarLL.getIdProduction("INI")}));
}

