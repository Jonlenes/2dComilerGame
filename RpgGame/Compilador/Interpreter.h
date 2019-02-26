#ifndef DRAWINTERPRETER_H
#define DRAWINTERPRETER_H

#include <string>
#include <vector>
#include <map>
using namespace std;



class Data {
public:
    Data(int key, int direction, int count, bool isKey):
        key(key), direction(direction), count(count), isKey(isKey) {}

    int key;
    int direction;
    int count;

    bool isKey;
};


class Interpreter
{
public:
    static Data *process(std::string source);

};

#endif // DRAWINTERPRETER_H
