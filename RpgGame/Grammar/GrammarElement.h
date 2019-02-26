#ifndef GRAMMARELEMENT_H
#define GRAMMARELEMENT_H

#include <iostream>

using namespace std;

class GrammarElement
{
public:
    GrammarElement();
    virtual ~GrammarElement() {}

    virtual bool isTerminal() = 0;
    virtual int getId() = 0;
};

#endif // GRAMMARELEMENT_H
