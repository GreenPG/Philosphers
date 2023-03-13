# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 16:30:04 by gpasquet          #+#    #+#              #
#    Updated: 2023/03/13 16:57:44 by gpasquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =	clang

CFLAGS =	-g -Werror -Wextra -Wall -pthread -fsanitize=thread -I./includes 

NAME =	philo	

SRCS =	srcs/main.c \
		srcs/args_functions.c \
		srcs/forks.c \
		srcs/check_args.c \
		srcs/utils.c \
		srcs/free_functions.c \
		srcs/life.c \
		srcs/death.c

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
