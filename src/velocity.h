//
//  velocity.h
//  Assign26
//
//  Created by Luc Comeau on 2/13/15.
//  Copyright (c) 2015 Luc Comeau. All rights reserved.
//

#ifndef __Assign26__velocity__
#define __Assign26__velocity__

#include <stdio.h>
#include "point.h"

class Velocity
{
private:
    double dx;
    double dy;
    Point pt;
    
public:
    Velocity() : pt(0,0), dx(0), dy(0) {};
    Velocity(float x, float y, float dx, float dy) : pt(x,y), dx(dx), dy(dy) {};
    
    float getX()  const    { return pt.getX(); };
    float getY()  const    { return pt.getY(); };
    float getDx() const    { return dx; };
    float getDy() const    { return dy; };
    Point getPoint() const { return pt; };
    
    void setX(float x)           { pt.setX(x);  };
    void setY(float y)           { pt.setY(y);  };
    void setDx(float x)          { dx = x;      };
    void setDy(float y)          { dy = y;      };
    void setPoint(Point newpt)   { pt = newpt;  };

    Velocity & operator =  (const Velocity & rhs);
    Velocity & operator ++ ();
    Velocity & operator ++ (int);
    Velocity   operator +  (const Velocity   rhs);
    Velocity & operator += (const Velocity & rhs);

    friend bool operator == (Velocity &lhs, float rhs);
    friend bool operator >  (Velocity &lhs, float rhs);
    friend bool operator >= (Velocity &lhs, float rhs);
    friend bool operator <  (Velocity &lhs, float rhs);
    friend bool operator <= (Velocity &lhs, float rhs);
    friend float operator - (Velocity &lhs, Velocity &rhs);
};

std::ostream & operator << (std::ostream & out, Velocity & vel);
bool operator == (Velocity &lhs, Velocity &rhs);
bool operator != (Velocity &lhs, Velocity &rhs);

#endif /* defined(__Assign26__velocity__) */
