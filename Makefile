# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 14:02:02 by mabriand          #+#    #+#              #
#    Updated: 2022/05/26 12:09:25 by mabriand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER		=	./server
CLIENT		=	./client
COMMON		=	common.a

##################################### PATH #####################################
SRC			=	./src/

#################################### SOURCES ###################################

#-----------------------------SERVER-#
SRC_SERVER	=	$(SRC)server.c \
				
#-----------------------------CLIENT-#
SRC_CLIENT	=	$(SRC)client.c \

#-----------------------------COMMON-#
SRC_COMMON	=	$(SRC)utils.c \
				$(SRC)libft.c
				
################################### INCLUDES ###################################

INC			=	./inc/

##################################### BASIC ####################################

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

OBJ_COMMON	=	$(SRC_COMMON:.c=.o)

##################################### RULES ####################################

all:		$(COMMON) $(CLIENT) $(SERVER)

$(COMMON):	$(OBJ_COMMON)
	ar	rc $(COMMON) $(OBJ_COMMON)

$(SERVER):	$(OBJ_SERVER)
		$(CC) $(CFLAGS) -I$(INC) -o $(SERVER) $(OBJ_SERVER) $(COMMON)

$(CLIENT):	$(OBJ_CLIENT)
		$(CC) $(CFLAGS) -I$(INC) -o $(CLIENT) $(OBJ_CLIENT) $(COMMON)

clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_COMMON)

fclean:	clean
	rm -f $(SERVER) $(CLIENT) $(COMMON)

re:	fclean all

.PHONY: all clean fclean re 