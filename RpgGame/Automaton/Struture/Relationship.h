#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include "State.h"

class Relationship {

public:

    Relationship();
    Relationship(State *stateDestination, const char &simboly);
    Relationship(State *stateDestination, bool (*function)(char));

    State *stateDestination;
    char simboly;
    bool (*function)(char);
};

#endif // RELATIONSHIP_H
