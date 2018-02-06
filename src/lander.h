#pragma once

#include "velocity.h"

class Lander
{
   private:
      Velocity vel;


   public:
      Lander();
      ~Lander();
      
      Point getPoint() const;
      float getX() const;
      float getY() const;
      float getDy() const;
      float getDx() const;
      void setX(float y);
      void setY(float y);

      void draw() const;
      void advance(int down, int left, int right, bool fuel);

};
