#include "AFD.h"
#include <stack>

AFD::AFD() : AF()
{

}

int AFD::readWordModified(const string &word, unsigned long long &index)
{
    stack<State *> stackStates;
    State *stateError;
    unsigned long long size = word.length();

    stackStates.push(initialState);
    do {
        stackStates.push(functionProgrammer(stackStates.top(), word[index]));
        if (!stackStates.top()) {
            stackStates.pop();
            stateError = !stackStates.empty()? stackStates.top() : nullptr;
            while (!stackStates.empty() && !stateIsFinal(stackStates.top())) {
                stackStates.pop();
                --index;
            }
            break;
        }
    } while (index++ < size);

    if (stackStates.empty())
        return stateError->getCategory();

    return (static_cast<FinalState *> (stackStates.top())->getCategory());
}
