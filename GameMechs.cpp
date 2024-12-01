#include "GameMechs.h"
#include "MacUILib.h"

// Default Constructor of GameMechs
GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = -1;

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
    score = -1;

    boardSizeX = boardX;
    boardSizeY = boardY;
    food.setObjPos(5, 5, '0');
}

// Nothing in destructor
// This is because there's no dynamic memory allocation ("new") in the constructors
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

// Collects the asynchronous user input (or key pressed)
void GameMechs::collectACInput() {
    if(MacUILib_hasChar()) {
        input = MacUILib_getChar();
    }
    
    // The space bar is the key to exit the game by default
    if (input == ' ') {
        setExitTrue();
    }
}

// Generates the coordinates and symbol of the food object
void GameMechs::generateFood(objPosArrayList* blockOff) {

    // Setting up random number generator
    srand(time(NULL));

    // Getting a copy of the blockOff (player) position data for access
    objPos playerPos = blockOff->getHeadElement();
    int x_coord = 0, y_coord = 0;
    bool posIdentical = true;

    // Loops until the player's (head & body) and food's position are different
    while (posIdentical) {
        posIdentical = false;
        x_coord = (rand() % (getBoardSizeX() - 2)) + 1;
        y_coord = (rand() % (getBoardSizeY() - 2)) + 1;

        // Checks the food's position to each body part of the snake (player) and determines whether they are the same
        for (int i = 0; i < blockOff->getSize(); i++) {
            objPos currentPart = blockOff->getElement(i);

            if (x_coord == currentPart.pos->x && y_coord == currentPart.pos->y) {
                posIdentical = true;
                break;
            }
        }

        // Calls the method to add to the score each time the player collects a food object
        incrementScore();
    }

    int ascii = playerPos.symbol;

    // Randomly generates the food's ASCII value (not same as player's character)
    while (ascii == playerPos.symbol) {
        ascii = (rand() % 94) + 33;
    }
    
    // Updates the new randomly generated food object
    food.setObjPos(x_coord, y_coord, ascii);
}

// Returns the food as an objPos
objPos GameMechs::getFoodPos() const {
    return food;
}

// Returns the food as the address of an objPos
objPos& GameMechs::getFood() {
    return food;
}