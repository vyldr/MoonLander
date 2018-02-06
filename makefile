###############################################################
# Program:
#     Project 2, Moon Lander
#     Brother Comeau, CS165
# Author:
#     Steven Wilde
# Summary:
#     This program is the game Moon Lander.  You play by pressing the arrow
#     keys to move the lander onto the platform.  I added an item that 
#     you can pick up to refill your fuel, a bar to display your 
#     remaining fuel, something to show where the lander is when 
#     it flies above the top of the window, and a background with 
#     stars that moves based on how the lander moves.  
#
#     Estimated:  0.0 hrs
#     Actual:     0.0 hrs
#       Please describe briefly what was the most difficult part
###############################################################

LFLAGS = -lglut -lGLU -lGL  # -lGL added so it compiles on my computer

###############################################################
# Programs:
#    moon:         The moon lander game
###############################################################
bin/moon: build/ground.o build/game.o build/uiInteract.o build/uiDraw.o build/point.o build/lander.o build/velocity.o
	g++ -o bin/moon build/*.o $(LFLAGS)

###############################################################
# Individual files
#    ground.o      Displays the ground and platform
#    game.o        The moon game
#    uiInteract.o  Handles input events
#    uiDraw.o      Drawing functions
#    point.o       Point class
#    lander.o      Lander class
#    velocity.o    Velocity class
#    stars.o       Stars class
###############################################################
build/ground.o: src/ground.cpp src/ground.h
	g++ -c src/ground.cpp -o build/ground.o

build/game.o: src/game.cpp src/uiDraw.h src/uiInteract.h src/point.h src/ground.h src/stars.h
	g++ -c src/game.cpp -o build/game.o

build/uiInteract.o: src/uiInteract.cpp src/uiInteract.h src/point.h
	g++ -c src/uiInteract.cpp -o build/uiInteract.o

build/uiDraw.o: src/uiDraw.cpp src/uiDraw.h src/point.h
	g++ -c src/uiDraw.cpp -o build/uiDraw.o

build/point.o: src/point.cpp src/point.h
	g++ -c src/point.cpp -o build/point.o

build/lander.o: src/lander.cpp src/lander.h src/velocity.h
	g++ -c src/lander.cpp -o build/lander.o

build/velocity.o: src/velocity.cpp src/velocity.h
	g++ -c src/velocity.cpp -o build/velocity.o
	
###############################################################
# General rules
###############################################################
clean:
	rm bin/moon build/*.o

all:
	bin/moon
	
again:
	make clean
	make
