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
		utils/ft_strlen.c					\
		utils/ft_strdup.c					\
		utils/ft_strndup.c					\
		utils/ft_strjoin.c					\
		test.c								\
		\
		exit.c								\
		t_linked_list.c						\
		p_tokenisation.c 					\
		pt_quotes.c							\
		pt_special.c						\
		pt_exploration.c					\
		ptt_typing_token.c					\
		pl_lexer.c							\
