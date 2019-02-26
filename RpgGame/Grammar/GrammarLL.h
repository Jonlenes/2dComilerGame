#ifndef GRAMMARLL_H
#define GRAMMARLL_H

#include <map>
#include "Grammar/Production.h"

using namespace std;

class GrammarLL
{
public:
    GrammarLL();
   ~GrammarLL();

    void addProduction(Production *production);
    Production *getProduction(string name, int indexElement);
    int getIdProduction(string name);
    string getProductionName(int id);
    bool isTerminal(int id);

private:
    map< pair<string, int>, Production *> mapProductions;
    map< string, int > mapNamesTerminais;
    vector< Production *> listNewProduction;
    int countTerminais;

    Production *getProductionAfim(map< pair<string, int>, Production *>::iterator &it, int indexElement);
};

#endif // GRAMMARLL_H
