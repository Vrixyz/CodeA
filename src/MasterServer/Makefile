NAME			=	MasterServer

CC			=	g++

SRC			=	src/OpSQL.cpp \
				src/Login.cpp \
				src/Client.cpp \
				src/Server.cpp \
				src/Socket.cpp \

OBJ			=	$(SRC:.cpp=.o)

LIB			=	-lsqlite3 -lmsgpack

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
