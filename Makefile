##
## EPITECH PROJECT, 2021
## B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
## File description:
## Makefile
##

## CORE ##

CORE                =    $(realpath ./core/)

## GAMES ##

NIBBLER             =    $(realpath ./libs/games/nibbler/)

PACMAN              =    $(realpath ./libs/games/pacman/)

## GRAPHIC ##

NCURSES             =    $(realpath ./libs/graphics/ncurses/)

SDL2                =    $(realpath ./libs/graphics/sdl2/)

SFML                =    $(realpath ./libs/graphics/sfml/)


all:				libs

libs:
					$(MAKE) -C $(CORE)
					$(MAKE) -C $(NIBBLER)
					$(MAKE) -C $(PACMAN)
					$(MAKE) -C $(NCURSES)
					$(MAKE) -C $(SDL2)
					$(MAKE) -C $(SFML)

core:
					$(MAKE) -C $(CORE)

games:
					$(MAKE) -C $(NIBBLER)
					$(MAKE) -C $(PACMAN)

graphicals:
					$(MAKE) -C $(NCURSES)
					$(MAKE) -C $(SDL2)
					$(MAKE) -C $(SFML)

clean:
					$(MAKE) -C $(CORE) clean
					$(MAKE) -C $(NIBBLER) clean
					$(MAKE) -C $(PACMAN) clean
					$(MAKE) -C $(NCURSES) clean
					$(MAKE) -C $(SDL2) clean
					$(MAKE) -C $(SFML) clean

fclean:
					$(MAKE) -C $(CORE) fclean
					$(MAKE) -C $(NIBBLER) fclean
					$(MAKE) -C $(PACMAN) fclean
					$(MAKE) -C $(NCURSES) fclean
					$(MAKE) -C $(SDL2) fclean
					$(MAKE) -C $(SFML) fclean

re:                 fclean all

.PHONY:             all libs core games graphicals clean fclean re