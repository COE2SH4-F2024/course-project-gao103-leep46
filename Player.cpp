#include "Player.h"
#include "GameMechs.h"

// Constructor
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();
    objPos headElement(mainGameMechsRef -> getBoardSizeX()/2, mainGameMechsRef -> getBoardSizeY()/2, '*');
    
    playerPosList -> insertHead(headElement);
}

// Copy Constructor
Player::Player(const Player &other){

    mainGameMechsRef = other.mainGameMechsRef;
    myDir = other.myDir;

    playerPosList = new objPosArrayList(*other.playerPosList);
}

// Copy Assignment Operator
// First checks whether the Player isn't identical
    // If not, itcopies the Player &other contents over
    // If so, nothing happens
Player& Player::operator= (const Player &other){

    if (this != &other){

        mainGameMechsRef = other.mainGameMechsRef;
        myDir = other.myDir;

        objPosArrayList* newPosList = new objPosArrayList(*other.playerPosList);
        delete playerPosList; // deletes old playerPosList to prevent memory leakage
        playerPosList = newPosList;
    }
    return *this;
}

// Destructor
Player::~Player()
{
    // Deletes any heap members here
    delete playerPosList;
}

// Returns the reference to the playerPos arrray list
objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
}

// Updates the player movement (direction)
void Player::updatePlayerDir()
{
        // PPA3 input processing logic  
        char input = mainGameMechsRef->getInput();     

        // Check whether the player pressed a key of the corresponding values to change movement
        switch(input){

            case ' ':  // exit case
                myDir = STOP;
                break;

            case 'W': case 'w':  // up case (only if not going down)
                if (myDir != DOWN){
                    myDir = UP;

                }
                break;

            case 'A': case 'a':  // left case (only if not going right)
                if (myDir != RIGHT){
                    myDir = LEFT;  
            
                }
                break;

            case 'S': case 's':  // down case (only if not going up)
                if (myDir != UP){
                    myDir = DOWN;  
                }
                break;

            case 'D': case 'd': // right case (only if not going left)
                if (myDir != LEFT){
                    myDir = RIGHT;  
                }
        
                break;
                
            default:  // otherwise, nothing happens
                break;
        }
}

// Updates the player movement on board
void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    updatePlayerDir();

    objPos newPos (playerPosList->getHeadElement().getObjPos().pos->x, playerPosList->getHeadElement().getObjPos().pos->y, '*');
    
    // Checks whether the direction of the snake (player) matches one of the following cases
    switch (myDir){
        case UP: // up case (changes the snake direction to move upwards and wrap-around boundaries)
            newPos.pos->y--;
            if (newPos.pos->y < 1) {  
                newPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        case DOWN: // down case (changes the snake direction to move downwards and wrap-around boundaries)
            newPos.pos->y++;
            if (newPos.pos->y >= mainGameMechsRef->getBoardSizeY() - 1) {  
                newPos.pos->y = 1;
            }
            break;
        case LEFT: // left case (changes the snake direction to move leftwards and wrap-around boundaries)
            newPos.pos->x--;
            if (newPos.pos->x < 1) {  
                newPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;
        case RIGHT: // right case (changes the snake direction to move rightwards and wrap-around boundaries)
            newPos.pos->x++;
            if (newPos.pos->x >= mainGameMechsRef->getBoardSizeX() - 1) {  
                newPos.pos->x = 1;
            }
            break;
        case STOP: // stop case (do nothing)
            break;
    }

    // If the snake (player) collides into food object, then the snake (player) grows (by not removing tail)
    // Otherwise, add the head to its upcoming position and remove the tail to show the snake "moving"
    if (newPos.pos->x == mainGameMechsRef->getFood().getObjPos().pos->x && newPos.pos->y == mainGameMechsRef->getFood().getObjPos().pos->y) {
        playerPosList->insertHead(newPos);
        mainGameMechsRef->generateFood(playerPosList);
    } else {
        playerPosList->insertHead(newPos);
        playerPosList->removeTail();
    }
    
    // If the snake collides into itself (with the method called), sets both the lose and exit flags to true
    if (checkSelfCollision()) {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
}

// Checks and returns (by boolean) whether the head of the snake collides into its body
bool Player::checkSelfCollision() {
    objPos newHead = getPlayerPos()->getHeadElement();

    // Checks each body part (after the head) and whether its coordinates match the head
    for (int i = 1; i < getPlayerPos()->getSize(); i++) {
        objPos currentBody = getPlayerPos()->getElement(i);

        // Returns true if the snake head collides into any part of body
        if (newHead.pos->x == currentBody.pos->x && newHead.pos->y == currentBody.pos->y) {
            return true;
        }
    }
    return false; // Returns false if no collision occurs
}