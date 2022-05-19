# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 14:02:02 by mabriand          #+#    #+#              #
#    Updated: 2022/05/19 11:44:56 by mabriand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER		=	./server
CLIENT		=	./client	

##################################### PATH #####################################
SRC			=	./src/

#################################### SOURCES ###################################

#-----------------------------SERVER-#
SRC_SERVER	=	$(SRC)server.c \
				$(SRC)utils.c \
				$(SRC)libft.c
				
#-----------------------------CLIENT-#
SRC_CLIENT	=	$(SRC)client.c \
				$(SRC)utils.c \
				$(SRC)libft.c

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