NAME			=	Server

CC			=	g++

SRC			=	Server.cpp \
				Socket.cpp \

OBJ			=	$(SRC:.cpp=.o)

LIB			=	-lmsgpack

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
				rm -f $(OBJ) *~

fclean			:	clean
				rm -f $(NAME)

re			:	fclean all
