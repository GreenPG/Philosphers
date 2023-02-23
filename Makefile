# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 16:30:04 by gpasquet          #+#    #+#              #
#    Updated: 2023/02/16 16:39:33 by gpasquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =	clang

CFLAGS =	-fsanitize=thread -g -Werror -Wextra -Wall -pthread -I./includes 

NAME =	philo	

SRCS =	srcs/main.c \
		srcs/args_functions.c \
		srcs/utils.c \
		srcs/free_functions.c

OBJS =	${SRCS:.c=.o}

all:	${NAME}

.c.o:
	@printf "Compiling .c to .o \r"
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
	
$(NAME): ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME} 
	@printf '\e[1;37m%-6s\e[m' "Compilation complete"

clean:
	@n=1; \
	for file in $(OBJS); do \
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

-include test.mk
