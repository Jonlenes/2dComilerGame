#include "Production.h"


Production::Production(string name, initializer_list<int> initElements)
    : name(name), listElements(initElements)
{
}

bool Production::isTerminal()
{
    return true;
}

void Production::setId(int id)
{
    this->id = id;
}

int Production::getId()
{
    return id;
}

string Production::getName()
{
    return name;
}

vector<int> *Production::getListElements()
{
    return &listElements;
}
