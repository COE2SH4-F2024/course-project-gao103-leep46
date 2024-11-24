#include "Player.h"
#include "GameMechs.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos = new Pos();

    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '*';
    
}

//copy constructor
Player::Player(const Player &other){

    mainGameMechsRef = other.mainGameMechsRef;
    myDir = other.myDir;

    playerPos.pos = new Pos(*(other.playerPos.pos));
    playerPos.symbol = other.playerPos.symbol;
}

//copy assignment operator
Player& Player::operator= (const Player &other){

    if (this != &other){
        delete playerPos.pos;

        mainGameMechsRef = other.mainGameMechsRef;
        myDir = other.myDir;

        playerPos.pos = new Pos(*(other.playerPos.pos));  
        playerPos.symbol = other.playerPos.symbol;
    }
    return *this;
}

Player::~Player()
{
    // delete any heap members here
    delete playerPos.pos;
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
        switch(input){

            case ' ':  // exit
                myDir = STOP;
                break;

            case 'W': case 'w':  
                if (myDir != DOWN){
                    myDir = UP;

                }
                break;

            case 'A': case 'a':  
                if (myDir != RIGHT){
                    myDir = LEFT;  
            
                }
                break;

            case 'S': case 's':  
                if (myDir != UP){
                    myDir = DOWN;  
                }
                break;

            case 'D': case 'd':
                if (myDir != LEFT){
                    myDir = RIGHT;  
                }
        
                break;
                
            default:
                break;
        }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    updatePlayerDir();
    // if (playerPos.pos->x)

    switch (myDir){
        case UP:
            playerPos.pos->y--;
            if (playerPos.pos->y < 1) {  
                playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        case DOWN:
            playerPos.pos->y++;
            if (playerPos.pos->y >= mainGameMechsRef->getBoardSizeY() - 1) {  
                playerPos.pos->y = 1;
            }
            break;
        case LEFT:
            playerPos.pos->x--;
            if (playerPos.pos->x < 1) {  
                playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;
        case RIGHT:
            playerPos.pos->x++;
            if (playerPos.pos->x >= mainGameMechsRef->getBoardSizeX() - 1) {  
                playerPos.pos->x = 1;
            }
            break;
        case STOP: 
            break;
    }
    
}

// More methods to be added