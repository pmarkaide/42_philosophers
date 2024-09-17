# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 12:01:03 by pmarkaid          #+#    #+#              #
#    Updated: 2024/09/17 16:57:47 by pmarkaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =                              \
	main.c 							\
	init.c							\
	routine.c

OBJS = $(SRCS:.c=.o)

CC = cc 
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lpthread
DEBUG_FLAGS = -Wall -Werror -Wextra -fsanitize=address

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

debug: $(OBJS)
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re debug