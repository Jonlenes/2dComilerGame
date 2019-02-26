#ifndef FUNCTIONSTYPECARACTER_H
#define FUNCTIONSTYPECARACTER_H

bool isDifferentOfendl(char caracter)
{
    return (caracter != '\n');
}

bool isDifferentOfAsterisk(char caracter)
{
    return (caracter != '*');
}

bool isDifferentOfBar(char caracter)
{
    return (caracter != '/');
}

bool isWhite(char caracter)
{
    return (caracter == ' ' || caracter == '\t');
}

bool isLineBreak(char caracter)
{
    return (caracter == '\n');
}

bool isDigit(char caracter) {
    return (caracter >= 48 && caracter <= 57);
}

bool isLatter(char caracter) {
    return ((caracter >= 65 && caracter <= 90) || (caracter >= 97 && caracter <= 122));
}

bool isUppercaseCharacter(char caracter) {
    return (caracter >= 65 && caracter <= 90);
}

bool isLowerCaseCharacter(char caracter) {
    return (caracter >= 97 && caracter <= 122);
}

bool isDelimiters(char caracter) {
    return (caracter == '(' || caracter == ')' || caracter == ',' ||
            caracter == ';' || caracter == '[' || caracter == ']');
}

bool isArithmeticOperators(char caracter) {
    return (caracter == '+' || caracter == '-' || caracter == '*'
            || caracter == '%');
}

bool isDifferentOfQuotationMarks(char caracter)
{
    return (caracter != '\'');
}

bool isDifferentOfDoubleQuotes(char caracter)
{
    return (caracter != '\"');
}

#endif // FUNCTIONSTYPECARACTER_H
