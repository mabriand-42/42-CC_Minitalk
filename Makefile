# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 14:02:02 by mabriand          #+#    #+#              #
#    Updated: 2022/01/27 14:13:51 by mabriand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER		=	./server	# Gives the name of the final output for the server and its location.
CLIENT		=	./client	

##################################### PATH #####################################
SRC			=	./src/

#################################### SOURCES ###################################

#-----------------------------SERVER-#
SRC_SERVER	=	$(SRC)server.c \
				$(SRC)utils.c \
				$(SRC)basic.c
				
#-----------------------------CLIENT-#
SRC_CLIENT	=	$(SRC)client.c \
				$(SRC)utils.c \
				$(SRC)basic.c

################################### INCLUDES ###################################

INC			=	./inc/

##################################### BASIC ####################################

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

##################################### RULES ####################################

all:		$(CLIENT) $(SERVER)

$(SERVER):	$(OBJ_SERVER)
		$(CC) $(CFLAGS) -I$(INC) -o $(SERVER) $(OBJ_SERVER)

$(CLIENT):	$(OBJ_CLIENT)
		$(CC) $(CFLAGS) -I$(INC) -o $(CLIENT) $(OBJ_CLIENT)

clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

fclean:	clean
	rm -f $(SERVER) $(CLIENT)

re:	fclean all

.PHONY: all clean fclean re 