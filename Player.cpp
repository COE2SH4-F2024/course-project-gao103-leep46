#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '@';
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic  
        char input = mainGameMechsRef->getInput();     

        // Switch cases down below   
        // switch(input):
        //  if (myDir != LEFT && myDir != RIGHT) {
        //    myDir = UP;
        //}
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    updatePlayerDir();
    // if (playerPos.pos->x)
}

// More methods to be added