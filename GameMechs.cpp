#include "GameMechs.h"
//#include "MAC LIBRARY"

GameMechs::GameMechs()
{
    // input = 0;
    // exitFlag = false;
    // loseFlag = false;
    // score = 0;

    // boardSizeX = 20;
    // boardSizeY = 10;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    // input = 0;
    // exitFlag = false;
    // loseFlag = false;
    // score = 0;

    // boardSizeX = boardX;
    // boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    // return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{

}
    

char GameMechs::getInput() const
{
    // FROM PPA2
    // Error: remove 'const' above since below if trying to update the var

    // if(MacUILib_hasChar()) {
    //  input = MacUILib_getChar();
    // }
    
    // if (input == ' ') {
    //  exitFlag = true;
    // }

    // return input;
}

int GameMechs::getScore() const
{

}

void GameMechs::incrementScore()
{
    
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{

}

void GameMechs::setLoseFlag()
{
    
}

void GameMechs::setInput(char this_input)
{

}

void GameMechs::clearInput()
{

}

// More methods should be added here