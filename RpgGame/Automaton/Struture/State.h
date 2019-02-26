#ifndef STATE_H
#define STATE_H

#include <iostream>

class State {
public:
    State(std::string name);
    State(std::string name, int category);

    int getCategory();

    std::string name;
    int index;

private:
    int category;
};

#endif // STATE_H
