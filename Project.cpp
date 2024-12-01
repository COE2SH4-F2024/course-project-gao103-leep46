#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

// Global Variables & Objects
GameMechs *myGM;
Player *myPlayer;
objPosArrayList *arrayList;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    // Looping the program until the exit flag (within the GameMech class) is true
    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }
    
    // Special message that's only displayed if the lose flag is true
    if (myGM->getLoseFlagStatus()) {
        MacUILib_printf("Game over! You collided into yourself.\n");
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Creating the GameMech and player objects
    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    // Randomly generating the food object
    myGM->generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{
    // Collecting asynchronous input and setting input key (if player presses a key)
    myGM->collectACInput();
    myGM->setInput(myGM->getInput());
}

void RunLogic(void)
{
    myPlayer->movePlayer(); // Moves the player position
    if(myGM->getInput() != 0)  // If the key pressed is not the null character
    {
        switch(myGM->getInput())
        {           
            // Exits game if player presses 'space'
            case ' ':  
                myGM->setExitTrue();
                break;
            default:
                break;
        }

        // Clear input field in GameMechs to avoid double-processing the input
        myGM->clearInput();
    }
}

void DrawScreen(void)
{

    MacUILib_clearScreen();

    // Storing positions of player (snake) and food as objPos objects
    objPosArrayList* playerPosList = myPlayer->getPlayerPos();
    objPos foodPos = myGM->getFoodPos();

    // Displays the board UI
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY(); 

    // Initializing coordinates of the food and player (snake) to be displayed
    int foodX = foodPos.pos->x;
    int foodY = foodPos.pos->y;
    char foodSymbol = foodPos.symbol;
    
    // First, draws the borders (30x15) with the # symbol
    // Then, draws the food object with its own symbol
    // Then, it draws the snake (body) with its own symbol
    // If the snake (body) isn't in a coordinate, an empty symbol ' ' is drawn over it instead
    for (int i = 0; i < boardY; i++) {
        for (int j = 0; j < boardX; j++) {
            if (i == 0 || j == 0 || i == boardY - 1 || j == boardX - 1) {
                MacUILib_printf("#");
            }
            else if (i == foodY && j == foodX) {
                MacUILib_printf("%c", foodSymbol);
            }
            else {
                char emptySpace = ' ';
                for (int k = 0; k < playerPosList->getSize(); k++){
                    objPos playerPos = playerPosList->getElement(k);
                    if (i == playerPos.pos->y && j == playerPos.pos->x){
                        emptySpace = playerPos.symbol;
                    }
                }
                MacUILib_printf("%c", emptySpace);
            }
        }
        MacUILib_printf("\n");
    }

    // Displays the player's score
    MacUILib_printf("Score: %d\n", myGM->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    // Deletes the objects to prevent memory leakage
    delete myPlayer;
    delete myGM;
    delete arrayList;
    MacUILib_uninit();
}
