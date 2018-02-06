#include "lander.h"
#include "uiDraw.h"


Lander::Lander()
{
   vel.setY(150);
   vel.setX(random(-150, 150));
}

Lander::~Lander()
{
}

void Lander::draw() const
{
   drawLander(vel.getPoint());
}

void Lander::advance(int down, int left, int right, bool fuel)
{
   float gravForce = -0.05;
   float accel = 0.05;
   float noAccel = 0.0;

   // Apply gravity
   Velocity grav(0, 0, noAccel, gravForce);
   vel += grav;
   
   // Use the engines
   if (fuel)
   {
      if (left)
      {
         Velocity tleft(0, 0, accel, noAccel);
         vel += tleft;
      }
      if (right)
      {
         Velocity tright(0, 0, -accel, noAccel);
         vel += tright;
      }
      if (down)
      {
         Velocity up(0, 0, 0, accel * 3);
         vel += up;
      }
   }
   vel++;
}

// Getters
Point Lander::getPoint() const { return vel.getPoint(); }
float Lander::getX()     const { return vel.getX();     }
float Lander::getDx()    const { return vel.getDx();    }
float Lander::getDy()    const { return vel.getDy();    }
float Lander::getY()     const { return vel.getY();     }

// Setters
void Lander::setX(float x) { vel.setX(x); }
void Lander::setY(float y) { vel.setY(y); }
