#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include "Compilador/Token.h"
#include "Automaton/AFD.h"

#include <vector>
#include <map>

using namespace std;

class Scanner
{
public:

    Scanner();
    Scanner(string source);
    ~Scanner();

    void setSource(string source);
    void deleteTokens();
    Token *nextToken();
    vector< pair<Token *, string> > getAllTokens();
    string getLexeme(int id);


private:
    string source;
    AFD *AFDReconhecedor;
    unsigned long long line;
    unsigned long long column;
    unsigned long long indexSource;

    map<string, int> mapIdTokens;
    map<int, string> mapNamesTokens;
    map<int, string> mapErrors;
    vector<Token *> listTokens;

    void monthMapIdToken();
    void monthMapNamesTokens();
    void monthMapErrors();

    void monthAfdReconhecedor();
    bool nextCaracterValid();

    void initVars();
    bool error(int id);
};

#endif // ANALISADORLEXICO_H
