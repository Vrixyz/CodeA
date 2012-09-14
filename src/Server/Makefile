##
## Makefile for  in /home/berger_t/PFA/src/Server
## 
## Made by thierry berger
## Login   <berger_t@epitech.net>
## 
## Started on  Fri Sep 14 10:58:16 2012 thierry berger
## Last update Fri Sep 14 11:09:22 2012 thierry berger
##

SRC	=	mainTest.cpp \
		World.cpp \
		Communication.cpp \
		Element.cpp \
		Unit.cpp \
		Bullet.cpp

NAME	=	server

OBJ	=	$(SRC:.cpp=.o)

LIBS	=	-lboost_system -lmsgpack -lBox2D

CXXFLAGS=	-W -Wall -Wextra

CC	=	g++

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) $(LIBS) -o $(NAME)

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all