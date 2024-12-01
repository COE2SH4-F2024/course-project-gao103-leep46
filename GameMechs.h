#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        int boardSizeX;
        int boardSizeY;

        // Food object (holds most recently generated food position and ASCII symbol)
        objPos food;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs(); // Not needed however
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput() const;
        void collectACInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore();
        
        // More methods should be added here
        void generateFood(objPosArrayList* blockOff); // Generates food object
        objPos getFoodPos() const; // Gets the food contents

        objPos& getFood(); // Gets the address of the food object
};

#endif