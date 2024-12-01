#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    public:
        // This is the direction state
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};

        // Constructor & Destructor
        Player(GameMechs* thisGMRef);
        ~Player();

        // Getter and other methods
        objPosArrayList* getPlayerPos() const;    
        void updatePlayerDir();
        void movePlayer();

    private:
        objPosArrayList* playerPosList;      
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;

        // Copy Constructor & Copy Assignment Operator
        Player(const Player &other);
        Player& operator= (const Player &other);

        // Added method that checks if snake (player) collides with itself
        bool checkSelfCollision();
};

#endif