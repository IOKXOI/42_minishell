/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:24:32 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/08 04:09:56 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_tok_name(enum e_special type)
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

	printf(RED"%10s: '%s'\n", get_tok_name(token->type), token->name);
	// if (token->next)
	// {
	// 	printf("next token = %s\n", token->next->name);
	// }
	printf("%s", WHT);
}

void	print_all_token(t_token *token)
{
	while (token)
	{
		print_node(token);
		token = token->next;
	}
}
