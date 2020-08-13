# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/29 17:09:53 by ksuomala          #+#    #+#              #
#    Updated: 2020/08/13 13:19:31 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c ft_get_grid.c backtracker.c

NAME = fillit

CC = gcc -Wall -Werror -Wextra -c

INCL = -I libft/

OBJS = $(SRCS:.c=.o)

LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	gcc -Wall -Werror -Wextra -o $(NAME) $(OBJS) $(LIB)

$(OBJS): $(SRCS) $(LIB)
	$(CC) $(SRCS) $(INCL)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

$(LIB):
	make -C libft/

lldb: $(OBJS)
	gcc -Wall -Werror -Wextra -g -o $(NAME) $(OBJS) $(LIB)
