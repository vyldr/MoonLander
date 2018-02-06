#pragma once
#include"velocity.h"
#include "uiDraw.h"

class Stars
{
   private:
      Point pt;
      //Point drawPt;
      float depth;
      
   public:
      Stars() : pt(random(pt.getXMin(), pt.getXMax()), random(-400.0, 400.0)), depth(random(-4.0, 1.5)) 
      { 
         if (depth < 0)
            depth = random(0.0, 1.0);
         //pt.setWrap(true);
      };
      //Stars(float x, float y) : vel(x, y) {};
      ~Stars() {};
      //void setX(float x) { pt.setX(x); }
      //void setY(float y) { pt.setY(y); }
      
      void draw(Point landPt) const
      {
         Point drawPt;
         drawPt.setWrap(true);
         drawPt.setX(-(landPt.getX() * depth) + pt.getX());
         drawPt.setY(-(landPt.getY() * depth) + pt.getY());
         drawDot(drawPt, depth);
      }
   
};
