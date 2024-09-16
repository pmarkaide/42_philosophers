# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 12:01:03 by pmarkaid          #+#    #+#              #
#    Updated: 2024/09/16 12:03:54 by pmarkaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_FILES =                              \
	main.c


SRC_DIR = philo/
SRCS = $(addprefix $(SRC_DIR), $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)

INCLUDE = -I philo/

CC = cc 
CFLAGS = -Wall -Werror -Wextra -g
DEBUG_FLAGS = -Wall -Werror -Wextra -fsanitize=address

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

debug: $(OBJS)
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re debug