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
		utils/only_space.c						\
		utils/ft_strlen.c					\
		utils/ft_strdup.c					\
		utils/ft_strndup.c					\
		utils/ft_strjoin.c					\
		\
		parsing/exit.c								\
		parsing/first_check_parse_error.c			\
		parsing/t_linked_list.c						\
		parsing/p_tokenisation.c 					\
		parsing/pt_quotes.c							\
		parsing/pt_special.c						\
		parsing/ptt_typing_token.c					\
		parsing/pl_lexer.c							\
		parsing/pa_aggregation.c					\
		parsing/paa_set_for_complete_commande.c		\
		parsing/pa_linked_list_init.c				\
		\
		test.c								
