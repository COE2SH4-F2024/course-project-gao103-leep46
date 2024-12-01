#include "objPos.h"

// Constructor (w/out parameters)
objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

// Constructor (w/ paramters)
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

// Destructor
objPos::~objPos() {
	delete pos;
}

// Copy Constructor
objPos::objPos(const objPos &o) {
	pos = new Pos{o.pos->x, o.pos->y};
    symbol = o.symbol;
}

//	Copy Assignment Operator
// For this operator, heap members are already allocated so need for "new" anymore
// First, checks whether the objPos is identical to the one being copied
    // If so, nothing happens
    // If not, proceed as follows
// Next, checks whether class exists
    // If not, this creates a new class with copied parameters
    // If it does, it copies the parameters from the other object to the current one
objPos& objPos::operator=(const objPos &o) {
	if (this != &o) {
        if (pos != nullptr) {
            delete pos; // Deletes old pos to prevent memory leakage
            pos = new Pos{o.pos->x, o.pos->y};
        } else {
            pos->x = o.pos->x;
            pos->y = o.pos->y;
        }
        symbol = o.symbol;
	}

	return *this;
}

// Setter for objPos (copies positions & symbol from other objPos object)
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

// Setter for objPos (copies positions & symbol from parameters)
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Getter for objpos (returns the positions & symbol)
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

// Getter for symbol
char objPos::getSymbol() const
{
    return symbol;
}

// Returns whether the position of two objPos objects are the same by boolean
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

// Returns whether the symbols of two objPos objects are the same by char
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
