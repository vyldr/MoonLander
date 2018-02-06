/****************************************
 * The game of moonlander
 ****************************************/

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "ground.h"
#include "lander.h"
#include "stars.h"

#define FUEL        500.0  // initial fuel for the game
#define MIN_SPEED   3.0    // minimal landing speed
#define FALL_HEIGHT 4.0    // greatest height we can fall from
#define STARS       1000

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   // create the game
   Game() : dead(false), landed(false), fuel(FUEL), left(0), right(0), up(0), 
            down(0), space(false), topLeft((lander.getPoint().getXMin() + 10), (lander.getPoint().getYMax() - 10)), 
            bonus(random(-170, 170), random(10, 170)), 
            bonusFlames(bonus.getX(), (bonus.getY() - 11)), bonusCaught(false), 
            textPosition(-30, 180), end(false) {}
   
   // handle user input
   void input(const Interface & ui);

   // advance the game
   void advance();
         
   // draw stuff
   void draw(const Interface & ui) const;
   
private:
   bool justLanded() const;
   
   int left;
   int right;
   int up;
   int down;
   bool space;
   
   Stars stars[STARS];
   int  fuel;
   bool dead;
   bool landed;
   bool end;
   Ground ground;
   Lander lander;
   Point textPosition;
   Point topLeft;
   Point bonus;
   Point bonusFlames;
   bool bonusCaught;
   
   // DONE: add any objects or variables that are required
};

/******************************************
 * GAME :: LANDED
 * Did we land successfully?
 ******************************************/
bool Game :: justLanded() const
{
   // DONE: indicate if the lander has landed
   if ((lander.getX() >= (ground.getPlatformX() - (ground.getPlatformWidth() / 2))) and 
       (lander.getX() <= (ground.getPlatformX() + (ground.getPlatformWidth() / 2))) and
       (lander.getY() <= (ground.getPlatformY() + 4)) and 
       (lander.getY() >= ground.getPlatformY()) and
       (sqrt(pow(lander.getDx(), 2) + pow(lander.getDy(), 2)) <= 3))
      {
         
         return true;
      }
   
   return false;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   landed = justLanded();
   if (landed)
   {
      if (!end)
      {
         std::cout << "Score: " << fuel << "\n";
         end = true;
      }
      lander.setX(ground.getPlatformX());
      lander.setY(ground.getPlatformY() + 1);
   }
   if (!landed and !dead)
   {
      lander.advance(down, left, right, fuel);
      dead = ground.crashed(lander.getPoint());
   }
   
   // Catch the bonus to reset fuel
   if ((sqrt(pow((lander.getX() - bonus.getX()), 2) + pow((lander.getY() - bonus.getY()), 2)) < 20) and !bonusCaught)
   {
      bonusCaught = true;
      fuel = 500;
   }
   
   // adjust fuel
   if (left)
      fuel--;
      
   if (right)
      fuel--;
      
   if (down)
      fuel -= 3;
      
   if (fuel < 0)
      fuel = 0;
   
}

/***************************************
 * GAME :: input
 * accept input from the user
 ***************************************/
void Game :: input(const Interface & ui)
{
   up = ui.isUp();
   down = ui.isDown();
   left = ui.isLeft();
   right = ui.isRight();
   space = ui.isSpace();
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui) const
{
   
   // draw the lander or a status message
   if (!dead)
   {
      lander.draw();
      
      if (fuel)
      {
         // These are separate statements to prevent flames from being drawn inside 
         // the lander when more than one is drawn.  
         drawLanderFlames(lander.getPoint(), down,  false, false);
         drawLanderFlames(lander.getPoint(), false, left,  false);
         drawLanderFlames(lander.getPoint(), false, false, right);
      }

      // Draw a marker to show where the lander is if it goes too high.  
      if (lander.getY() > lander.getPoint().getYMax() + 10)
      {
         Point marker(lander.getX(), lander.getPoint().getYMax() - 10);
         drawCircle(marker, 8, 8, 0);
         marker.setY(lander.getPoint().getYMax() - 21);
         if (fuel)
         {
            drawLanderFlames(marker, down,  false, false);
            drawLanderFlames(marker, false, left,  false);
            drawLanderFlames(marker, false, false, right);
         }
      }
         
   }
      
   if (landed)
      drawText(textPosition, "You successfully landed!");
   if (dead)
      drawText(textPosition, "You crashed!");
      
   for (int i = 0; i < STARS; i++)
      stars[i].draw(lander.getPoint());
      
   // draw the fuel level
   drawNumber(topLeft, fuel);
   
   // Draw a bar for the remaining fuel
   Point begin(0, 50);
   Point end(0, (fuel / FUEL * end.getYMax() * 0.6 + 50.0));
   for (int i = (begin.getXMin() + 10); i < (begin.getXMin() + 20); i++)
   {
      begin.setX(i);
      end.setX(i);
      drawLine(begin, end, (1.0 - (fuel / FUEL)), (fuel / FUEL), 0.0);
   }

   // draw the bonus fuel
   if (!bonusCaught)
   {
      drawRect(bonus, 6, 16, 0);
      drawLanderFlames(bonusFlames, true, false, false);
   }


   // draw the ground
   ground.draw();
}

#define X_SIZE       800

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   Game *pGame = (Game *)p;
   
   pGame->advance();
   
   pGame->input(*pUI);
   
   pGame->draw(*pUI);
}

// set the bounds of the drawing rectangle
float Point::xMin = -(X_SIZE / 2.0);
float Point::xMax =  (X_SIZE / 2.0);
float Point::yMin = -400.0;
float Point::yMax =  400.0;

/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Moon Lander");
   Game game;
   ui.run(callBack, &game);
   
   return 0;
}
