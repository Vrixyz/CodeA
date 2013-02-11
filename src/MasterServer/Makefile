NAME			=	test_sql

CC			=	g++

SRC			=	src/main.cpp \
				src/Login.cpp

OBJ			=	$(SRC:.cpp=.o)

LIB			=	-lsqlite3

DEBUG			=	no

ifeq ($(DEBUG),yes)
	XXFLAGS	=	-W -Wall -ansi -pedantic -g
else
	XXFLAGS	=	-W -Wall -ansi -pedantic
endif

all                     :       $(NAME)

$(NAME)                 :       $(OBJ)
				$(CC) -o $(NAME) $(OBJ) $(XXFLAGS) $(LIB)

clean                   :
				rm -f $(OBJ) src/*~ include/*~

fclean			:	clean
				rm -f $(NAME)

re			:	fclean all
