#include "Scanner.h"
#include "Util/GeneralFunctions.h"
#include "Compilador/Enums.h"


Scanner::Scanner()
{
    initVars();

    monthMapIdToken();
    monthAfdReconhecedor();
    monthMapErrors();
}

Scanner::Scanner(string source)
    : source(source)
{
    initVars();

    monthMapIdToken();
    monthAfdReconhecedor();
    monthMapErrors();
}

Scanner::~Scanner()
{
    deleteTokens();
}


Token *Scanner::nextToken() {
    int id;
    unsigned long long indexBeginToken;
    Token *token;

    if(!nextCaracterValid())
        return nullptr;

    indexBeginToken = indexSource;
    id = AFDReconhecedor->readWordModified(source, indexSource);

    if (error(id))
        throw string("Erro Léxico: " + mapErrors[id] + "\nLinha " + to_string(line) + ", Coluna " +
                     to_string(column));

    token = new Token(id, source.substr(indexBeginToken, indexSource - indexBeginToken),
                      Position(line, column));
    column += (indexSource - indexBeginToken);

    if (id == Identifier)
        token->setId(mapIdTokens[token->getLexeme()]);

    return token;
}

vector< pair<Token *, string> > Scanner::getAllTokens()
{
    vector< pair<Token *, string> > listTokens;
    Token *token;

    while (token = nextToken(), token) {
        listTokens.push_back(make_pair(token, ""));
    }

    return listTokens;
}

bool Scanner::nextCaracterValid()
{
    unsigned long long size = source.length();
    char caracter;

    while(indexSource < size) {
        caracter = source[indexSource];

        if (isWhite(caracter))
            column++;
        else if (isLineBreak(caracter)) {
            line++;
            column = 0;
        } else
            return true;

        indexSource++;
        column++;
    }

    return false;
}

void Scanner::initVars()
{
    line = 1;
    column = 1;
    indexSource = 0;
}

bool Scanner::error(int id)
{
    return (id >= 1000);
}

void Scanner::setSource(string source)
{
    this->source = source;
    initVars();
}

void Scanner::deleteTokens()
{
    for (auto item : listTokens) {
        if (item) delete item;
    }

    listTokens.clear();
}

string Scanner::getLexeme(int id)
{
    if (id >= 50 && id <= 999) {
        for (auto item : mapIdTokens) {
            if (item.second == id)
                return item.first;
        }
    } else
		return mapNamesTokens[id];
	
	return "";
}

void Scanner::monthMapErrors()
{
    mapErrors[InvalidCaracter] = "caracter inválido.";
    mapErrors[WaitingDigit] = "esperando um número depois do \'.\'. ";
    mapErrors[WaitingForOr] = "esperando um \'|\' para formar o operador lógico \'||\'. ";
    mapErrors[WaitingForAnd] = "esperando um \'&\' para formar o operador lógico \'&&\'. ";
    mapErrors[WaitingCloseCaracter] = "esperando \'.";
    mapErrors[WaitingCloseComment] = "esperando fechar comentário.";
    mapErrors[WaitingCloseString] = "esperando \" .";
}

void Scanner::monthMapIdToken()
{
    //------------------------------------------------------------
    string keyWords[] = {"A", "D", "S", "M", "L", "R", "U"};
    int countKeyWord = sizeof(keyWords) / sizeof(keyWords[0]);

    for(int i = 0; i < countKeyWord; ++i)
        mapIdTokens[keyWords[i]] = i + 100;
    //------------------------------------------------------------
}

void Scanner::monthAfdReconhecedor()
{
    AFDReconhecedor = new AFD();

    //estado inicial
    AFDReconhecedor->addState(new State("s0", InvalidCaracter), false, true);


    //---------------------------INDENTIFICADORES--------------------------------
    AFDReconhecedor->addState(new FinalState("s1", Identifier), true);

    AFDReconhecedor->addRelaptionament("s0", "s1", &isUppercaseCharacter);
    //---------------------------------------------------------------------------


    //--------------------------------INTEIRO------------------------------------
    AFDReconhecedor->addState(new FinalState("s4", Integer), true);

    AFDReconhecedor->addRelaptionament("s0", "s1", &isDigit);
    AFDReconhecedor->addRelaptionament("s1", "s1", &isDigit);
    //---------------------------------------------------------------------------

}
