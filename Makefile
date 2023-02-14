# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 16:30:04 by gpasquet          #+#    #+#              #
#    Updated: 2023/02/14 16:30:46 by gpasquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =	clang

CFLAGS =	-g -Werror -Wextra -Wall -I./includes 

NAME =	philo	

SRC =	srcs/main.c \

OBJ =	${SRC:.c=.o}

all:	${NAME}

.c.o:
	@printf "Compiling .c to .o \r"
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
	
$(NAME): ${OBJ}
	@${CC} ${CFLAGS} ${OBJ} -o ${NAME} 
	@printf '\e[1;37m%-6s\e[m' "Compilation complete"

clean:
	@n=1; \
	for file in $(OBJ); do \
		if test -e $$file; then \
			if [ $$n -eq 1 ]; then \
				printf "Cleaning .o files \n"; \
			fi; \
			n=$$((n + 1)); \
			rm $$file; \
		fi \
	done

fclean:	clean
	@n=1; \
	if test -e ${NAME}; then \
		if [ $$n -eq 1 ]; then \
			printf "Cleaning files\n"; \
		fi; \
		n=$$((n + 1)); \
		rm ${NAME}; \
	fi

re:	fclean all

.PHONY:	all clean fclean re 
