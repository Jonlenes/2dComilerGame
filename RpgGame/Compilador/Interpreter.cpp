#include "Interpreter.h"
#include "Parser.h"
#include <string.h>

Data *Interpreter::process(string source)
{
    Parser parser(source);
    if (!parser.execute())
        return nullptr;

    vector<Token *> tokens = parser.getTokens();

    if (tokens.size() == 0)
        return nullptr;

    if (tokens.size() == 1)
        return new Data(atoi(tokens[0]->getLexeme().c_str()), -1, -1, true);
    else {
        int move;

        if (tokens[2]->getLexeme() == "L")
            move = 0;
        else if (tokens[2]->getLexeme() == "U")
            move = 1;
        else if (tokens[2]->getLexeme() == "R")
            move = 2;
        else
            move = 3;

        return new Data(-1, move, atoi(tokens[1]->getLexeme().c_str()), false);
    }

    return nullptr;
}
