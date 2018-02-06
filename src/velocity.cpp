/***********************************************************************
* File: velocity.cpp
* Summary: 
*    Velocity class
************************************************************************/

#include "velocity.h"
#include "point.h"
#include <cmath>

// These defines will be usefull for the operator -
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define DELTA          0.001

/**********************************************************************
 * Operator << 
 *********************************************************************/
std::ostream & operator << (std::ostream & out, Velocity & vel)
{
    // Sample output "(0,0) [9,9]"
    out << vel.getPoint() << " [" << vel.getDx() << ", " << vel.getDy() << "]";
    return out;
}

/**********************************************************************
 * Operator == with code to handle a Delta
 *********************************************************************/
bool operator == (Velocity &lhs, Velocity &rhs)
{
    return (fabs(lhs.getX() - rhs.getX()) < DELTA &&
            fabs(lhs.getY() - rhs.getY()) < DELTA &&
	    fabs(lhs.getDx() - rhs.getDx()) < DELTA &&
	    fabs(lhs.getDy() - rhs.getDy()) < DELTA );
}

/**********************************************************************
 * Operator !=
 *********************************************************************/
bool operator != (Velocity &lhs, Velocity &rhs)
{
    return !(lhs == rhs);
}

/**********************************************************************
 * Operator == with code to handle a Delta
 *********************************************************************/
bool operator == (Velocity &lhs, float rhs)
{
   return (fabs(sqrt(pow(lhs.dx, 2) + pow(lhs.dy, 2)) - rhs) < DELTA);
}

/**********************************************************************
 * Operator >  
 *********************************************************************/
bool operator >  (Velocity &lhs, float rhs)
{
   //std::cout << sqrt(pow(lhs.dx, 2) + pow(lhs.dx, 2));
   return ((sqrt(pow(lhs.dx, 2) + pow(lhs.dy, 2)) > rhs) and !(lhs == rhs));
}

/**********************************************************************
 * Operator <  
 *********************************************************************/
bool operator <  (Velocity &lhs, float rhs)
{
   return ((sqrt(pow(lhs.dx, 2) + pow(lhs.dy, 2)) < rhs) and !(lhs == rhs));
}

/**********************************************************************
 * Operator <= 
 *********************************************************************/
bool operator <= (Velocity &lhs, float rhs)
{
   return ((lhs < rhs) or (lhs == rhs));
}

/**********************************************************************
 * Operator >= 
 *********************************************************************/
bool operator >= (Velocity &lhs, float rhs)
{
   return ((lhs > rhs) or (lhs == rhs));
}

/**********************************************************************
 * Operator - 
 *********************************************************************/
float operator -  (Velocity &lhs, Velocity &rhs)
{
    return (sqrt(pow(fabs(lhs.getX() - rhs.getX()), 2) + pow(fabs(lhs.getY() - rhs.getY()), 2)));
}

/**********************************************************************
 * Operator = 
 *********************************************************************/
Velocity & Velocity :: operator =  (const Velocity & rhs)
{
   this->dx = rhs.dx;
   this->dy = rhs.dy;
   //float tx = rhs.getX();
   //float ty = rhs.getY();
   this->setX(rhs.getX());
   this->setY(rhs.getY());
   return *this;
}

/**********************************************************************
 * Operator ++
 *********************************************************************/
Velocity & Velocity :: operator ++ ()
{
   this->setX(this->dx + this->getX());
   this->setY(this->dy + this->getY());
   return *this;
}

Velocity & Velocity :: operator ++ (int)
{
   this->setX(this->dx + this->getX());
   this->setY(this->dy + this->getY());
   return *this;
}

/**********************************************************************
 * Operator +
 *********************************************************************/
Velocity   Velocity :: operator +  (const Velocity rhs) 
{
   return Velocity(this->getX(), this->getY(), this->dx + rhs.dx, this->dy + rhs.dy);
}

/**********************************************************************
 * Operator +=
 *********************************************************************/
Velocity & Velocity :: operator += (const Velocity & rhs)
{
   dx += rhs.dx;
   dy += rhs.dy;
   return *this;
}
