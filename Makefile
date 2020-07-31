# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/29 17:09:53 by ksuomala          #+#    #+#              #
#    Updated: 2020/07/30 18:00:33 by ksuomala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c

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
