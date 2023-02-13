/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:24:32 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/13 02:43:37 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_tok_name(enum e_type type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == IN_FILE)
		return ("IN_FILE");
	else if (type == OUT_FILE)
		return ("OUT_FILE");
	else if (type == SINGLE_Q)
		return ("SINGLE_Q");
	else if (type == DOUBLE_Q)
		return ("DOUBLE_Q");
	else if (type == HERE_DOC)
		return ("HERE_DOC");
	else if (type == LIMITER)
		return ("LIMITER");
	else if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (type == OUT_FILE_APPEND)
		return ("OUT_FILE_APPEND");
	else if (type == FILES)
		return ("FILES");
	else if (type == WORD)
		return ("WORD");
	else if (type == CMD)
		return ("CMD");
	else if (type == START)
		return ("START");
	else if (type == END)
		return ("END");
	else if (type == SPACE_BIS)
		return ("SPACE_BIS");
	else 
		return ("UNKNOWN");
}

void	print_node(t_token *token)
{
// 	printf(YLW"token:\nname = %s\n\
// first = %p\n\
// type = %d\n\
// prev = %p\n\
// next = %p\n", token->name, token->first, token->type, token->prev, token->next);
// 	if (token->next)
// 	{
// 		printf("next token = %s\n", token->next->name);
// 	}

	printf(RED"%20s: '%s'\n", get_tok_name(token->type), token->name);
	// if (token->next)
	// {
	// 	printf("next token = %s\n", token->next->name);
	// }
	printf("%s", YLW);
}

void	print_all_token(t_token *token)
{
	while (token)
	{
		print_node(token);
		token = token->next;
	}
}
