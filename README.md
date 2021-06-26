# arcade_2020
#### Simulation of an arcade machine made in C++ using SDL2, SFML and ncurses libraries. 

## Preview
![Alt Text](https://s6.gifyu.com/images/Arcade_vid.gif)

## Usage
	./arcade [lib_name.so]

## Commands
	[directional arrows] for the up/down/left/right directions
	[r] Reset the game
	[o] Load the first game
	[p] Load the second game
	[b] Load the previous graphical library
	[n] Load the next graphical library
	[del] Go back to the main menu
	[Enter] Confirm your name in the game over screen
	[Escape] Quit the program

## Libraries location
Libraries are located in the /lib folder after you compiled the project

## How to run the project

### Under Fedora
Install the prerequisites :

	> sudo dnf install SDL2 SDL2-devel SDL2_ttf SDL2_ttf-devel SFML SFML-devel ncurses ncurses-devel
Then :

	> git clone git@github.com:cram0/arcade_2020.git && cd arcade_2020
	> mkdir lib/games/score && touch lib/games/score/nibbler_score lib/games/score/pacman_score
	> make
	> ./arcade lib/arcade_sdl2.so
  
Check the [Libraries location] part to find where the libs are.

## Disclaimer
You might want to resize your terminal to a bigger size before you load the NCurses library for the borders to be shown properly.

## Authors
[cram0](https://github.com/cram0)<br>
[mariuscontoli](https://github.com/mariuscontoli)<br>
[EloiseRi](https://github.com/EloiseRi)
