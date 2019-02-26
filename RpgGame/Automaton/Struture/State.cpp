#include "State.h"

State::State(std::string name)
    : name(name)
{

}

State::State(std::string name, int category) : name(name), category(category)
{

}

int State::getCategory()
{
    return category;
}

