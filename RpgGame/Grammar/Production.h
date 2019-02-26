#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "Grammar/GrammarElement.h"
#include <vector>
#include <iostream>

using namespace std;

class Production : public GrammarElement
{
public:
    Production();
    Production(string name, initializer_list<int> initElements);


    bool isTerminal() override final;
    void setId(int id);
    int getId() override final;
    string getName();
    vector<int> *getListElements();

private:
    string name;
    int id;
    vector<int> listElements;
};

#endif // PRODUCTION_H
