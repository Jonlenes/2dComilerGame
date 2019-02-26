#ifndef ENUMS_H
#define ENUMS_H

/********************[TOKENS - 1:999]*************************/
//0 a 49
enum IdToken {
    Identifier = 0,
    Integer
};


enum KeyWord{
    A,
    D,
    S,
    M,
    L,
    R,
    U
};


/*************************************************************/





/*******************[ERROS - 1000:1999]***********************/
//1000 a 1250
enum LexicalError  {
    InvalidCaracter = 1000,
    WaitingDigit,
    WaitingForOr,
    WaitingForAnd,
    WaitingCloseCaracter,
    WaitingCloseComment,
    WaitingCloseString
};
/*************************************************************/






/*******************[PRODUCÕES - 2000: inf]*******************/
enum Productions {
    Epsilon = -1
};

/*************************************************************/

#endif // ENUMS_H
