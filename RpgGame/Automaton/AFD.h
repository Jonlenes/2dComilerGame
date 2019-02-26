#ifndef AFD_H
#define AFD_H

#include "AF.h"

class AFD : public AF
{
public:
    AFD();
    int readWordModified(const string &word, unsigned long long &index);

};
#endif // AFD_H
