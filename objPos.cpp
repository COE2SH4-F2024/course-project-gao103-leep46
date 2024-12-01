#include "objPos.h"

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule
//      Destructor
objPos::~objPos() {
	delete pos;
}

//		Copy Constructor
objPos::objPos(const objPos &o) {
	pos = new Pos{o.pos->x, o.pos->y};
    symbol = o.symbol;
}

//		Copy Assignment Operator
// For this operator, heap members are already allocated so need for "new" anymore
// Checks whether class exists, if not, thne creates a new class with copied parameters
// If it does, it copeies the parameters from the other object to the current one
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


void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
