#include "GrammarLL.h"

#include <QDebug>

GrammarLL::GrammarLL()
{
    countTerminais = 0;
}

GrammarLL::~GrammarLL()
{

    for (auto item : mapProductions) {
        delete item.second;
        item.second = __null;
    }

    for (auto item : listNewProduction) {
        if (item) delete item;
    }

    mapProductions.clear();
    listNewProduction.clear();
}

void GrammarLL::addProduction(Production *production)
{

    if (mapNamesTerminais.find(production->getName()) == mapNamesTerminais.end()) {
        production->setId(countTerminais++ + 2000);
        mapNamesTerminais[production->getName()] = production->getId();
    } else
        production->setId(mapNamesTerminais[production->getName()]);

    mapProductions[make_pair (production->getName(), production->getListElements()->front())] = production;
}

Production *GrammarLL::getProduction(string name, int indexElement)
{
    auto i = mapProductions.find(make_pair(name, indexElement));
    if (i != mapProductions.end())
        return i->second;

    for (auto it = mapProductions.begin(); it != mapProductions.end(); ++it) {
        if ((*it).first.first == name && isTerminal((*it).first.second))
            return getProductionAfim(it, indexElement);
    }

    return nullptr;
}


Production *GrammarLL::getProductionAfim(map< pair<string, int>, Production *>::iterator &it, int indexElement)
{
    Production *production;
    string name = (*it).first.first;

    do {
        if (isTerminal((*it).first.second)) {
            production = getProduction( getProductionName((*it).first.second), indexElement );

            if (production) {

                Production *newProdution = new Production("", {});
                copy(production->getListElements()->begin(), production->getListElements()->end(), back_inserter(*newProdution->getListElements()));
                copy(++(*it).second->getListElements()->begin(), (*it).second->getListElements()->end(), back_inserter(*newProdution->getListElements()));

                return newProdution;
            }
        }
    } while ((*(++it)).first.first == name);

    return nullptr;
}

int GrammarLL::getIdProduction(string name)
{
    if (mapNamesTerminais.find(name) == mapNamesTerminais.end())
        mapNamesTerminais[name] = countTerminais++ + 2000;

    return mapNamesTerminais.find(name)->second;
}

string GrammarLL::getProductionName(int id)
{
    for (auto i : mapNamesTerminais) {
        if (i.second == id)
            return i.first;
    }

    return "";
}

bool GrammarLL::isTerminal(int id)
{
    return (id >= 2000);
}
