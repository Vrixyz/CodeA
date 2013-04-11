NAME			=	MasterServer

CC			=	g++

SRC			=	src/User.cpp \
				src/Client.cpp \
				src/Server.cpp \
				src/Server_base.cpp \
				src/Server_login.cpp \
				src/Server_util.cpp \
				src/Server_manage.cpp \
				src/Server_command.cpp \
				src/Server_succes.cpp \
				src/Socket.cpp \
				src/SQLManager.cpp \
				src/GameServer.cpp \

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
