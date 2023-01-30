# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 15:27:37 by sydauria          #+#    #+#              #
#    Updated: 2023/01/26 15:41:42 by sydauria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
SRC=main.c\
	linked_list.c\
	test.c\

INCLUDES=includes
CC=cc
CFLAGS= -Wall -Werror -Wextra
BUILD=build
LIBFT= ./libft


OBJS := $(SRC:%.c=$(BUILD)/%.o)

all: $(NAME)

-include:$(DEPS)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT) all --quiet
	$(CC) $(OBJS) -I $(INCLUDES) -L $(LIBFT) -lft -o $@

$(BUILD)/%.o: %.c ./includes/*.h
	@mkdir -p '$(@D)'
	$(CC) $(CFLAGS) -I $(INCLUDES) -L $(LIBFT) -lft -c $< -o $@


clean:
	$(MAKE) -C $(LIBFT) fclean
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean
	make

.PHONY: all clean fclean re
