NAME = combat_game
CC = g++
CFLAGS = -Wall -Wextra -std=c++17
INC = -Iinclude
SRC = src/main.cpp src/Character.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(INC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all