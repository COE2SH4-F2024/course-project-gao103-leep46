#include "Player.h"
#include "GameMechs.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPosList = new objPosArrayList();
    objPos headElement(mainGameMechsRef -> getBoardSizeX()/2, mainGameMechsRef -> getBoardSizeY()/2, '*');
    
    playerPosList -> insertHead(headElement);
    //int centerX = mainGameMechsRef->getBoardSizeX() / 2; // X-coordinate of the center
    //int centerY = mainGameMechsRef->getBoardSizeY() / 2; // Y-coordinate of the center
    //playerPosList->insertHead(objPos(centerX, centerY, '*'));       // Head
    //playerPosList->insertTail(objPos(centerX, centerY + 1, '*'));  // Body segment
    //playerPosList->insertTail(objPos(centerX, centerY + 2, '*'));  // Tail segment
}

//copy constructor
Player::Player(const Player &other){

    mainGameMechsRef = other.mainGameMechsRef;
    myDir = other.myDir;

    playerPosList = new objPosArrayList(*other.playerPosList);
}

//copy assignment operator
Player& Player::operator= (const Player &other){

    if (this != &other){

        mainGameMechsRef = other.mainGameMechsRef;
        myDir = other.myDir;

        objPosArrayList* newPosList = new objPosArrayList(*other.playerPosList);
        delete playerPosList; // deletes old playerPosList
        playerPosList = newPosList;
    }
    return *this;
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list

    return playerPosList;
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


    objPos newPos (playerPosList->getHeadElement().getObjPos().pos->x, playerPosList->getHeadElement().getObjPos().pos->y, '*');
    switch (myDir){
        case UP:
            newPos.pos->y--;
            if (newPos.pos->y < 1) {  
                newPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        case DOWN:
            newPos.pos->y++;
            if (newPos.pos->y >= mainGameMechsRef->getBoardSizeY() - 1) {  
                newPos.pos->y = 1;
            }
            break;
        case LEFT:
            newPos.pos->x--;
            if (newPos.pos->x < 1) {  
                newPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;
        case RIGHT:
            newPos.pos->x++;
            if (newPos.pos->x >= mainGameMechsRef->getBoardSizeX() - 1) {  
                newPos.pos->x = 1;
            }
            break;
        case STOP: 
            break;
    }

    // If the snake (player) collides into food object, then the snake (player) grows (by not removing tail)
    if (newPos.pos->x == mainGameMechsRef->getFood().getObjPos().pos->x && newPos.pos->y == mainGameMechsRef->getFood().getObjPos().pos->y) {
        playerPosList->insertHead(newPos);
        mainGameMechsRef->generateFood(playerPosList);
    } else {
        playerPosList->insertHead(newPos);
        playerPosList->removeTail();
    }
    
    if (checkSelfCollision()) {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
}

// More methods to be added
bool Player::checkSelfCollision() {
    objPos newHead = getPlayerPos()->getHeadElement();

    for (int i = 1; i < getPlayerPos()->getSize(); i++) {
        objPos currentBody = getPlayerPos()->getElement(i);

        // Returns false if the snake head collides into any part of body
        if (newHead.pos->x == currentBody.pos->x && newHead.pos->y == currentBody.pos->y) {
            return true;
        }
    }
    return false; // Returns true if no collision occurs
}