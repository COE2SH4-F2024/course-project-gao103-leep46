#include "GameMechs.h"
#include "MacUILib.h"

// Default Constructor of GameMechs
GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;
    food.setObjPos(5, 5, '0');
}

// Parameterized Constructor of GameMechs (given board size parameters)
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;
    food.setObjPos(5, 5, '0');
}

// Do you need a destructor?
// No, since there's no dynamic memory allocation ("new") in the constructors
GameMechs::~GameMechs()
{
    
}

// Returns the exit flag boolean value
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

// Returns the lose flag boolean value
bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    
// Returns the user's pressed key
// Gets the exit flag to true if user presses 'space'
char GameMechs::getInput() const 
{
    return input;
}

// Returns the score
int GameMechs::getScore() const
{
    return score;
}

// Increments the score by 1 when called
void GameMechs::incrementScore()
{
    score++;
}

// Returns the width of the board size
int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

// Returns the height of the board size
int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

// Sets the exit flag to true when called (to exit the game)
// User pushing 'space' for this to occur
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

// Sets the lose flag to true when called (to exit the game)
// User loses the game for this to occur
void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

// Sets player input to the character passed as the parameter
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

// Clears the most recently collected ASCII character input
// This is to ensure no input is double processed
void GameMechs::clearInput()
{
    input = '\0';
}

// More methods should be added here

// Collects the asynchronous user input (or key pressed)
void GameMechs::collectACInput() {
    if(MacUILib_hasChar()) {
        input = MacUILib_getChar();
    }
    
    if (input == ' ') {
        setExitTrue();
    }
}

void GameMechs::generateFood(objPos blockOff) {

    srand(time(NULL));

    // Getting a copy of the blockOff (player) position data for access
    // Default: declaring the food's (x,y) coordinates to match the player to go into while loop
    objPos playerPos = blockOff.getObjPos();
    int x_coord = playerPos.pos->x, y_coord = playerPos.pos->y;

    // Loops until the player's and food's position are different
    while (x_coord == playerPos.pos->x && y_coord == playerPos.pos->y) {
        x_coord = (rand() % (getBoardSizeX() - 2)) + 1;
        y_coord = (rand() % (getBoardSizeY() - 2)) + 1;
    }

    int ascii = playerPos.symbol;

    // Randomly generates the food's ASCII value (not same as player's character)
    while (ascii == playerPos.symbol) {
        ascii = (rand() % 94) + 33;
    }
    
    // Updates the new randomly generated food object
    food.setObjPos(x_coord, y_coord, ascii);

    // Cleaning deynamically allocated memory
    delete playerPos.pos;
}
        
objPos GameMechs::getFoodPos() const {
    return food;
}