##
## EPITECH PROJECT, 2021
## B-OOP-400-NCE-4-1-arcade-marius.contoli-legay
## File description:
## Makefile
##

NAME        =       ../arcade

SRC         =       $(shell find . -name '*.cpp')

OBJ         =       $(SRC:.cpp=.o)

CXXFLAGS    +=      -Wall
CXXFLAGS    +=      -Wextra
CXXFLAGS    +=      -Wno-unused-parameter
CXXFLAGS    +=      -I./include -I../lib/vendor

all         :       $(NAME)

$(NAME)     :       $(OBJ)
					g++ $(CXXFLAGS) -o $(NAME) $(OBJ) -g -O0 -ldl

clean       :
					find . -name "*.o" -type f -delete
					find . -name "vgcore.*" -type f -delete

fclean      :       clean
					rm -f $(NAME)

re          :       fclean all