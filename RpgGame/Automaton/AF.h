#ifndef AF_H
#define AF_H

#include <vector>
#include <map>

#include "Automaton/Struture/FinalState.h"
#include "Automaton/Struture/Relationship.h"

using namespace std;

class AF {

public:
    AF();
    virtual ~AF();

    virtual void addState(State *state, bool isFinal = false, bool isInitial = false);
    virtual void addRelaptionament(const string &stateBegin, const string &stateEnd, const char &simboly);
    virtual void addRelaptionament(const string &stateBegin, const string &stateEnd, bool (*function)(char));
    virtual State *functionProgrammer(const State *stateActual, const char simboly) ;
    bool stateIsFinal(const State *const &state) const;

protected:
    vector<State*> listStates;
    vector< vector<Relationship *> *> relaptionaments;
    map<string, int> mapAuto;
    State* initialState;
    vector<State *> finalStages;


    virtual void addRelaptionamentPrivate(const string &stateBegin, Relationship *relationship);
};

#endif // AF_H
