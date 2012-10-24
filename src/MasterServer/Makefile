CC		=	g++

NAME		=	master

SRC		= 	$(wildcard src/*.cpp)

OBJ		=	$(SRC:.cpp=.o)

INC		=	-I./include

LIB		=	-lsqlite3

CXXFLAGS	=	-W $(INC)

$(NAME):	all

all:		$(OBJ)
		$(CC) -o $(NAME) $(LIB) $(OBJ)

clean:		
		rm -f $(OBJ)

cleanf:		clean
		rm -f $(NAME)

re:		cleanf all