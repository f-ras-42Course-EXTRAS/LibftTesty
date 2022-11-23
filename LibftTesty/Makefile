# **************************************************************************** #
#
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fras <fras@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/08 20:56:28 by fras          #+#    #+#                  #
#    Updated: 2022/10/10 19:50:02 by fras          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #
# NOTE:
# Put files in PARENT FOLDER of libft to Work.


NAME = LibftTesty
CC = gcc
CFLAGS = -Werror -Wextra -Wall
SOURCE = LibftTesty.c
TESTSUBJECT = libft/libft.a
HEADER = libft/include/libft.h
INCLUDE = -I libft/include

.PHONY: all clean fclean re bonus speedtest leakscheck debug leaksinfo alldebugchecks

ifdef WITH_BONUS
BONUS = BONUSMODE
endif

$(NAME): $(SOURCE) $(TESTSUBJECT) $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) $< -L. $(TESTSUBJECT) -o $@

$(TESTSUBJECT):
	$(MAKE) -C libft

test: $(NAME) bonus $(TESTSUBJECT)
	./$< $(CANDIDATE) $(BONUS)

testbonus: bonus test

all: $(NAME) $(TESTSUBJECT) bonus

clean:
	rm -f *.o
	$(MAKE) $@ -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) $@ -C libft

re: fclean all

bonus:
	$(MAKE) $@ -C libft
	WITH_BONUS=1
	$(MAKE) $(NAME)

## EXTRA TESTING
speedtest: $(NAME)
	./$< SPEEDMODE

leakscheck: $(NAME)
	leaks --atExit -- ./$< SPEEDMODE

debug: $(SOURCE) $(NAME)
	$(CC) $(CFLAGS) -g -fsanitize=address $< -L. $(NAME) -o $@
	./$@ SPEEDMODE

leaksinfo: $(NAME)
	export MallocStackLogging=1 && \
	./$< SPEEDMODE && \
	leaks -atExit -quiet -list -- ./$< SPEEDMODE

alldebugchecks: debug leakscheck