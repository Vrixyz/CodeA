##
## Makefile for  in /home/berger_t/PFA/src/Server
## 
## Made by thierry berger
## Login   <berger_t@epitech.net>
## 
## Started on  Fri Sep 14 10:58:16 2012 thierry berger
## Last update Fri Apr 12 11:25:42 2013 mathieu leurquin
##

SRC_SR	=	mainTest.cpp \
		World.cpp \
		Element.cpp \
	 	Portal.cpp \
		Mage.cpp \
		Minion.cpp \
		IUnit.cpp \
		Bullet.cpp \
		tcp_connection.cpp \
		BitField.cpp \
		Object.cpp

SRC_CL	=	clientTest.cpp

NAME_CL =	client

NAME_SR =	server

OBJ_CL	=	$(SRC_CL:.cpp=.o)

OBJ_SR	=	$(SRC_SR:.cpp=.o)

LIBS	=	-lboost_system -lmsgpack -lBox2D -lboost_thread -lpthread -lm

CXXFLAGS=	-Wall -Wextra -ansi -g

CC	=	g++

all		:	$(NAME_SR)

$(NAME_CL)	:	$(OBJ_CL)
			$(CC) $(OBJ_CL) $(LIBS) -o $(NAME_CL)

$(NAME_SR)	:	$(OBJ_SR)
			$(CC) $(OBJ_SR) $(LIBS) -o $(NAME_SR)

clean		:
			rm -f $(OBJ_SR)
			rm -f $(OBJ_CL)

fclean		:	clean
			rm -f $(NAME_SR)
			rm -f $(NAME_CL)

re		:	fclean all
