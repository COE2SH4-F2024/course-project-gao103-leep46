#include <iostream>
#include "MacUILib.h"
#include "objPos.h"


#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

// Global Variables & Objects
// Pointer to GameMechs class
GameMechs *myGM;
Player *myPlayer;

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

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Creading the GameMech and player objects
    myGM = new GameMechs();
    myPlayer = new Player(myGM);

    // Randomly generating the food object
    myGM->generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{
    myGM->collectACInput();
    myGM->setInput(myGM->getInput());
}

void RunLogic(void)
{
    myPlayer->movePlayer();
    if(myGM->getInput() != 0)  // if not null character
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
    objPos playerPos = myPlayer->getPlayerPos();
    objPos foodPos = myGM->getFoodPos();

    // Displays the board UI
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY(); 

    // Initializing coordinates of the food and player (snake) to be displayed
    int foodX = foodPos.pos->x;
    int foodY = foodPos.pos->y;
    char foodSymbol = foodPos.symbol;
    
    int playerX = playerPos.pos->x;
    int playerY = playerPos.pos->y;
    char playerSymbol = playerPos.symbol;

    for (int i = 0; i < boardY; i++) {
        for (int j = 0; j < boardX; j++) {
            if (i == 0 || j == 0 || i == boardY - 1 || j == boardX - 1) {
                MacUILib_printf("#");
            } else if (i == playerY && j == playerX) {
                MacUILib_printf("%c", playerSymbol);
            } else if (i == foodY && j == foodX) {
                MacUILib_printf("%c", foodSymbol);
            } else {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //delete myPlayer;
    //delete myGM;
    MacUILib_uninit();
}
