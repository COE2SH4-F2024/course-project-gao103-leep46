#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

//#include "GameMechs.h"
//#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

//Player *myPlayer;
//GameMechs *myGM;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();


    while(exitFlag == false)  
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
    //myGM = new GameMechs();
    //myPlayer = new Player(myGM);

    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    //myPlayer->movePlayer();
}

void DrawScreen(void)
{
    int i, j; // i is height, j is width
    int width = 20; 
    int height = 10;

    MacUILib_clearScreen();    
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                MacUILib_printf("#");
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
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
