#include "Relationship.h"

Relationship::Relationship()
    : stateDestination(nullptr), function(nullptr)
{

}

Relationship::Relationship(State *stateDestination, const char &simboly)
    : stateDestination(stateDestination), simboly(simboly), function(nullptr)
{

}

Relationship::Relationship(State *stateDestination, bool (*function)(char))
    : stateDestination(stateDestination), function(function)
{

}
