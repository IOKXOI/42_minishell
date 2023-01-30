/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:18:54 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/29 17:25:27 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// #include "libft.h"
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <limits.h>

#define ERR printf(RED "The line %d, files %s have a problem" WHT, __LINE__, __FILE__);
#define RED "\033[31m"
#define YLW "\033[33m"
#define WHT "\033[30m"

enum token{
	HERE_DOC = 1,
	IN_FILE,
	OUT_FILE,
	OUT_FILE_APPEND,
	PIPE,
	CMD,
	ARG,
	LIMITER,
};

typedef struct s_token {
	char			token;
	char			*name;
	struct s_token	*first;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

int 	ft_strlen(char *str);
char	*ft_strdup(const char *s);

//test.c ////////////////////////////////////////////////////////////////////
void	print_node(t_token *token);
void	print_all_token(t_token *token);

//linked_list.c/////////////////////////////////////////////////////////////
t_token	*init_node();
t_token	*create_new_node(t_token *existing_node);

// exit.c //////////////////////////////////////////////////////////////////
//free list from first node;
void	*free_list(t_token *list);

# endif
