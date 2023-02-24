/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_parse_error.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 00:01:20 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/24 00:46:16 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_white_space_nodes(t_token *token_list)
{
	int d = 0;
	while (token_list)
	{
		if (token_list->type == SPACE_BIS)
		{
			token_list = free_node(token_list);
		}		
		printf("boucle = %d\n", d++);
		token_list = token_list->next;
	}
}

bool	check_redir_parse_error(t_token *token_list)
{
	bool	space_checker;

	space_checker = false;
	while (token_list)
	{
		if (token_list->type == REDIR_IN || token_list->type == REDIR_OUT)
		{
			token_list = token_list->next;
			while (token_list && token_list->type == SPACE_BIS)
			{
				token_list = token_list->next;
				space_checker = true;
			}
			if (token_list 
				&& (token_list->type == REDIR_IN || token_list->type == REDIR_OUT || token_list->type == PIPE)
				&& space_checker == true)
			{
				printf("syntax error near unexpected token `%s'\n", token_list->name);
				return (false);
			}
		}
		token_list = token_list->next;
	}
	return (true);
}

bool	check_pipe_parse_error(t_token *token_list)
{
	bool	space_checker;

	space_checker = false;
	while (token_list)
	{
		if (token_list->type == PIPE)
		{
			token_list = token_list->next;
			while (token_list && token_list->type == SPACE_BIS)
			{
				token_list = token_list->next;
				space_checker = true;
			}
			if (token_list 
				&& (token_list->type == PIPE)
				&& space_checker == true)
			{
				printf("syntax error near unexpected token `%s'\n", token_list->name);
				return (false);
			}
		}
		token_list = token_list->next;
	}
	return (true);
}

bool	first_check_parse_error(t_token *token_list)
{
	if (check_redir_parse_error(token_list) == false)
		return (false);
	if (check_pipe_parse_error(token_list) == false)
		return (false);
	free_white_space_nodes(token_list);
	return (true);
}

