# Battleship
## Proposal 
### Period 4 
### Members
  - Brandon Chen 
  - Maisha Miah
  - Bryan Monge Serrano

### Description
    We are creating a terminal based Battleship game. It is a 2 players turn based game with two screens/windows 
    per player. The goal of
    the game is to be the first to guess all coordinates of the opposing player’s ships on a xy plane. One 
    screen will display your ship
    positions as well as the guesses of your opponent while the other will display your guesses.

### How It Will Be Used
    The game will be terminal based so the user plays the game through the use of commands.
      - Help - display all of the instructions and commands needed to play the game.
      - Exit - exits the game/program
      - Place x y vertical/horizontal - places a ship either vertical or horizontal starting at the x and y 
      coordinate of the board and 
      going down/to the right.
      - Display mine/theirs - display the current state of the user’s/opponent’s board.
      - Attack x y - attacks the coordinate of the opponent’s board.

### Technical Design
    Networking - To allow 2 players to play against each other.
    
    Allocating memory - To save any necessary game data.
    
    Working with files - Used to record board status as well as game history by reading/writing to a file.
    
    Processes - Used to cat/display game history file. At the end, user will be prompted to delete game 
    history file or keep it for bragging rights by exporting it elsewhere.
    
    Data Structure: A struct and array to keep track of remaining ships and the board. 

### Required Libraries:
	  apt-get instructions 

### Timeline
    January 6 - Create home screen, make sure it will display on two computers
    January 10 - Make a way for the player to type coordinates to set up their ships 
    January 13 - Make sure it is interactive, that the coordinates that one player chooses to attack will be sent 
    to the other player
    January 15 - All critical aspects should be done 
    January 16 - Make any final adjustments or additions

