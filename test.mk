# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 11:03:28 by gpasquet          #+#    #+#              #
#    Updated: 2023/03/07 09:26:36 by gpasquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##########################	FILES	############################################

TSRCS = $(shell find unit_tests -name '*.c')

TRUNNER =	run_tests

TOBJS =	$(TSRCS:%.c=%.o)


##########################	CMDS	############################################

test: VALGRIND :=	valgrind \
									--quiet					\
									--leak-check=full		\
									--show-leak-kinds=all	\
									--error-exitcode=1 	\

test: test.build
	$(VALGRIND) ./run_tests

test.build:
	$(MAKE) -s --jobs=8 $(TRUNNER)

test.clean:
	@rm unit_tests/*.o
	@rm -rf $(NAME)
	@rm -rf $(TRUNNER)

fclean: test.clean

test.re: test.clean test

.PHONY:	test test.build test.clean test.re

$(TRUNNER):	OBJS	:=	$(filter-out %/main.o, $(OBJS))

$(TRUNNER): $(OBJS) $(TOBJS)
	$(CC) $(CFLAGS) $(OBJS) $(TOBJS) -o $(TRUNNER)

#$(TOBJS):	
#/	$(CC) $(CFLAGS) -c $(TSRCS) -o $(TOBJS)



