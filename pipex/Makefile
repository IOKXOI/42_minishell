# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 02:27:26 by sydauria          #+#    #+#              #
#    Updated: 2022/12/21 00:38:07 by sydauria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=pipex
CC=gcc
CFLAGS=-Wall -Werror -Wextra -MMD -g3
SRCDIR= srcs/
OBJSDIR=./objs/
BUILD = build
INCLUDES =./includes
LIBFT = ./libft

SRC_PARSING=$(addprefix parsing/, \
					paths_parsing.c \
					pid.c \
					check.c)

SRC_CHAIN_LIST=$(addprefix chain_list/, \
				create_list.c)
				
SRC_EXEC=$(addprefix exec/, \
			exec.c )

SRC_FREE=$(addprefix free/, \
			error.c \
			free.c)
		
SRCS=$(addprefix $(SRCDIR), \
		$(SRC_PARSING) \
		$(SRC_CHAIN_LIST) \
		$(SRC_EXEC) \
		$(SRC_FREE) \
		$(SRC_BONUS) \
		pipex.c)

################################################################################
#                                     OBJECTS                                  #
################################################################################

OBJS := $(SRCS:%.c=$(BUILD)/%.o)

################################################################################
#                                     RULES                                    #
################################################################################

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
