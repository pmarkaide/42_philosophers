# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 12:01:03 by pmarkaid          #+#    #+#              #
#    Updated: 2024/09/30 15:39:28 by pmarkaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_FILES =                        \
	main.c 							\
	main_utils.c 					\
	utils.c							\
	routine.c						\
	monitor.c

SRC_DIR = src/
SRCS = $(addprefix $(SRC_DIR), $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)

INCLUDE = -I ./include/

CC = cc 
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lpthread
DEBUG_FLAGS = -Wall -Werror -Wextra -fsanitize=address

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LDFLAGS) -o $(NAME)

debug: $(OBJS)
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) $(OBJS) $(INCLUDE) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug