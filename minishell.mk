NAME		:= minishell
CC			:= cc
CFLAGS 		:= -Wall -Wextra -Werror
LBSD        := $(pkg-config --libs libbsd) -lreadline
SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= includes

SRCS := 									\
		main.c								\
		\
		test.c								\
		exit.c								\
		linked_list.c						\
		pt_quotes.c							\
		p_tokenisation.c 					\
		pt_exploration.c					\
		\
		utils/ft_strdup.c					\
		utils/ft_strndup.c					\
		utils/ft_strlen.c					\
