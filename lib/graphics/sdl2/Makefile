##
## EPITECH PROJECT, 2021
## B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
## File description:
## Makefile
##

NAME           =        ../../arcade_sdl2.so

SRC            =        $(shell find . -name '*.cpp') \
						../../../core/src/AClock.cpp


OBJ            =        $(SRC:.cpp=.o)

CXXFLAGS       +=       -Wall
CXXFLAGS       +=       -Wextra
CXXFLAGS       +=       -Wno-unused-parameter
CXXFLAGS       +=       -shared -fPIC
CXXFLAGS       +=       -I./include -I../../vendor -I../../vendor/SDL2 -I../../../core/include

all            :        $(NAME)

$(NAME)        :        $(OBJ)
						g++ $(CXXFLAGS) -o $(NAME) $(OBJ) -lSDL2 -lSDL2_ttf

clean          :
						find . -name "*.o" -type f -delete
						find . -name "vgcore.*" -type f -delete

fclean         :        clean
						rm -f $(NAME) $(NAME)

re             :        fclean all