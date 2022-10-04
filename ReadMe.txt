*******************************************************
*  Name      :  Michael Hoover        

*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

The program allows the user to play a game of battleship against the computer. It allows the user to place the ships at the beginning of the game and to guess shots throughout the game. The program generates ship placement and shots for the computer player. It terminates when either side wins the game or when the user wants to quit.

Extra Credit: The program fills requirements for two extra credit options. 

1) Ships can only be sunk if they have been hit at every grid coordinate they occupy. For instance, a Battleship must by hit four times before it is sunk. The program will continue to play the game until one of the players sinks all 5 opponent ships. 

2) The program has a strategy for the computer player that goes beyond random guesses. If the computer player has hit an opponent ship and that ship has not been sunk, then it will use a decision tree to attack that particulare ship. If there is only one hit on the ship it will randomly guess an adjacent coordinate to the hit. If there is more than one hit then the computer player will determine the orientation for the ship from the previous hits and guess a coordinate that is both adjacent to a hit and in line with the orientation of the ship. If there are no ships that have been hit but not sunk the computer player will guess randomly in a checkered pattern so as to maximize the efficeincy of its guesses. 

Note on Grading: In the main.cpp file there are two lines of code marked as comments. They are lines 97 & 98. If you remove the comments markers from these lines then the program will display the placement of the computer player ships at the beginning of the game. Otherwise the program will not display the position of the computer ships until the end of the game. 


*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
	Main program file. It creates 2 Player objects, one for the user and one for the computer. It opens a file and calls the necessary function to read ships from the file and place them on the grid for the user player. It catches exceptions from the functions (an exception will be thrown if the placement of ships is illegal.) Then it calls the function to generate random ship placement for the computer. 
	Then the program begins a loop for the players to take turns. Before every turn it checks the win conditions to see if either player has won. The loop will continue until one of the players win of the user decides to quit the game. When one of the players wins it will output the result of the game to the screen. 

Name:  grid.h
	Header file for Grid class. It provides the definition for the class Grid and declarations of member functions. It also provides definitions for a number of classes that are used to throw exceptions. These classes are intentionally left blank

Name:  grid.cpp
	Defines class member functions for the Grid class, including constructors, mutators, and accessors. 

Name: player.h
	Header file for Player class. It provides a definition of the class and declares class functions.

Name: player.cpp
	Defines member functions for class Player. In addition to constructors, mutators, and accessors the file defines takeTurn(), which alternates turns between the user and computer, comGuessDecision(), a function that implements a strategy for the computer player, and checkHit(), a function that checks to see if the player guess hit an opponent ship.

Name: shipPlacement.h 
	Header file for ShipPlacement class. It provides a definition for class ShipPlacement and declarations for member functions.

Name: shipPlacement.cpp
	Defines member functions for ShipPlacement class. The file defines constructors, mutators and accessors. It also defines readShipsFromFile(), a function that accepts data from and input file for the placement of the user's ships, placeOneShipOnGrid(), a function that places a ship on the grid and checks to make sure it is a legal placements, printShipPlacement(), a function that outputs the placement of the ships to the screen, and randomShips(), a function that randomly selects ship locations for the computer player. 

Name: guesses.h
	Header file for Guesses class. It provides a definition of the class and declares class functions.

Name: guesses.cpp
	Defines member functions for Guesses class. The file defines constructors, mutators and accessors. It also provides a defintion for userGuess(), a function that prompts the user to input a guess and checks that the input is legal, computerGuess(), a function that generates a random guess for the computer player, printGuesses, a function that outputs the guess grid to the screen, and checkGuess(), a function that checks if a guess has hit an enemy ship.

Name: ship.h
	Header file for Guesses class. It provides a definition of the class and declares class functions.

Name: ship.cpp
	Defines member functions for Ship class. It defines constructors, mutators, and accessors. The file also defines addHit(), a function that increments the number of hits a ship has taken by 1 and then checks to see if the latest hit was enough to sink the ship. 
	

   
*******************************************************
*  Status of program
*******************************************************

The program runs successfully.  
  
The program was developed on Clion and tested on the csegrid. 

The program completes requirements for extra credit in addition to the basic requirements of the assignment.	

******************************************************
* How to build and run the program
******************************************************

1. uncompress the zip file named HooverHW5.zip

	You should see a directory named HW5 with the following files:
		grid.cpp
		grid.h
		guesses.cpp
		guesses.h
		Hoover_DesignDocument_FinalProject.pdf
		main.cpp
		Makefile
		player.h
		player.cpp
		ReadMe.txt
		ship.cpp
		ship.h
		shipPlacement.cpp
		ShipPlacement.h
		ship_placement1_good.csv
		ship_placement2_good.csv
		ship_placement3_good.csv
		ship_placement4_good.csv
		ship_placement5_good.csv
		ship_placement6_good.csv
		ship_placement7_good.csv
		ship_placement8_good.csv
		ship_placement1_bad.csv
		ship_placement10_bad.csv

2. Compile the program by typing the command:
	make

3. Run the program by typing the command:
	./HooverHW5.exe

4. Delete the object files by typing the command:
	make clean
	
