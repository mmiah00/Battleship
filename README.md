# Battleship

## Team and Period
Brandon Chen, Maisha Miah, Bryan Monge Serrano Period 4

## Description
This project is a terminal-based version of Battleship the board game. Battleship is a 2 player turn based game with networking serving as the connection. To start, each player place down 5 ships of sizes 2, 3, 3, 4, and 5 on a 8x8 board. After both players placed their ships, they take turns guessing and attacking coordinates where they think an enemy ship is located. Once the other player's fleet has entirely been eliminated, you win. In our project, we used a struct and 2d array to manage the board and ships. ~ represents water, H represents a ship, O represents a successful hit, and X represents a failed hit. When attacking, details will be recorded by writing to the history.txt file. When prompted to display history, the history.txt file will be catted. When the victory conditions are fufilled, players will be prompted to decide where to export their history file to keep as bragging rights.

## Required Libraries

## Instructions
After running make run, you will be welcomed by the introscreen, which will ask you to set up the game either as a client or a server. There must be one client and one server, and the server must connect first. Then you will be told to place your ships by first typing in the coordinates then either 'h' for horizontal or 'v' for vertical. After both players are done placing their ships, the game will start and will continue on a turn basis. Each player will choose the coordinates they want to attack and runs until a player has attacked each of the other player's ships. 

In order to run the networking version of the game, you must type 'make' then './battleship' or 'make run'

In order to run the nonetworking version of the game, you must type './nonetworking' after typing 'make'

## Other information
### Bugs
Exporting isn't quite there yet. When entering '.' or '..' to export history file, it instead gets content copied or renamed to a file called '.'
or '..' as a dot file.
