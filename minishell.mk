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
		\
		exit.c								\
		first_check_parse_error.c			\
		t_linked_list.c						\
		p_tokenisation.c 					\
		pt_quotes.c							\
		pt_special.c						\
		ptt_typing_token.c					\
		pl_lexer.c							\
		pa_aggregation.c					\
		paa_set_for_complete_commande.c		\
		pa_linked_list_init.c				\
		\
		test.c								
