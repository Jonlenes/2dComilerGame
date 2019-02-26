#include "AF.h"
#include <sstream>

AF::AF() {}

AF::~AF()
{
    for (auto item : listStates) {
        if (item) delete item;
    }

    listStates.clear();
}

void AF::addState(State *state, bool isFinal, bool isInitial)
{

    state->index = static_cast<int> (listStates.size());
    mapAuto[state->name] = state->index;
    listStates.push_back(state);
    relaptionaments.push_back(nullptr);

    if (isInitial)
        initialState = listStates[listStates.size() - 1];
    if (isFinal)
        finalStages.push_back(state);

}

void AF::addRelaptionament(const string &stateBegin, const string &stateEnd, const char &simboly)
{
    addRelaptionamentPrivate(stateBegin, new Relationship(listStates[mapAuto.at(stateEnd)], simboly));
}

void AF::addRelaptionament(const string &stateBegin, const string &stateEnd, bool (*function)(char))
{
    addRelaptionamentPrivate(stateBegin, new Relationship(listStates[mapAuto.at(stateEnd)], function));
}

void AF::addRelaptionamentPrivate(const string &stateBegin, Relationship *relationship)
{
    try {
        int index = mapAuto.at(stateBegin);
        if (!relaptionaments[index])
            relaptionaments[index] = new vector<Relationship *> ();
        static_cast<vector<Relationship *> *> (relaptionaments[index])->push_back(relationship);
    } catch(...) {
        throw string("State does not exist.");
    }
}

State *AF::functionProgrammer(const State *stateActual, const char simboly)
{
    vector<Relationship*> *relationActual = relaptionaments[stateActual->index];
    if(!relationActual) return nullptr;

    for (auto item : *relationActual) {
        Relationship *relationship = static_cast<Relationship*> (item);
        if ((relationship->function && (*relationship->function)(simboly)) || (!relationship->function && relationship->simboly == simboly))
            return relationship->stateDestination;
    }

   return nullptr;
}

bool AF::stateIsFinal(const State *const &state) const
{
    for (auto item : finalStages)
        if (item == state) return true;

    return false;

}
