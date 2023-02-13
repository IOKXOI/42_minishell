/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:46:02 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/13 01:53:59 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	pipe_analyser(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == PIPE)
		{
			if (token_list->next->type == PIPE)
				return (false);
			// else if (token_list->next->type == END)
			// 	return (false);
		}
		token_list = token_list->next;
	}
	return (true);
}

static bool	redirect_analyser(t_token *token_list)
{	
	while (token_list)
	{
		if (token_list->type == REDIR_IN || token_list->type == REDIR_OUT || token_list->type == REDIR_OUT_APPEND || token_list->type == HERE_DOC)
		{
			if (token_list->name = REDIR_IN && token_list->next->type == REDIR_OUT)
				return (true);
			else if (token_list->next->type == REDIR_IN)
				return (false);
			else if (token_list->next->type == REDIR_OUT)
				return (false);
			else if (token_list->next->type == REDIR_OUT_APPEND)
				return (false);
			else if (token_list->next->type == HERE_DOC)
				return (false);
			else if (token_list->next->type == END)
				return (false);
		}
		token_list = token_list->next;
	}
	return (true);
}

bool	syntax_analyser(token_list)
{
	if (pipe_analyser(token_list) == false)
		return (printf("syntax error near unexpected token `|'"), false);
	else if (redirect_analyser(token_list) == false)
		return (printf("syntax error near unexpected token `>'"), false);
	return (true);
}

bool	p_lexeur(t_token	*token_list)
{
	if (syntax_analyser(token_list) == false)
		return (false);
	else
		return (true);
}
