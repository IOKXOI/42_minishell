/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptt_typing_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:03:17 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/07 04:43:07 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*fusion_node(enum e_special type, t_token *token, t_token *next)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit_minishell(token);
	new->name = ft_strjoin(token->name, next->name);
	if (!new->name)
		exit_minishell(token);
	new->type = type;
	new->prev = token->prev;
	new->next = next->next;
	if (token->prev)
		token->prev->next = new;
	if (next->next)
		next->next->prev = new;
	free(token->name);
	free(next->name);
	free(token);
	free(next);
	return (new);
}

void	ptt_redir_in(t_token *token)
{
	if (token->next->type == REDIR_IN)
	{
		token = fusion_node(HEREDOC, token, token->next);
		if (token->next->type == WORD)
			token->next->type = LIMITER;
		// else
		// 	token->next->type = ERROR;
	}
	else if (token->next->type == WORD)
		token->next->type = IN_FILE;
	// else
	// 	token->next->type = ERROR;
}

void	ptt_redir_out(t_token *token)
{
	if (token->next->type == REDIR_OUT)
	{
		token = fusion_node(REDIR_APPEND, token, token->next);
		if (token->next->type == WORD)
			token->next->type = OUT_FILE;
		// else
		// 	token->next->type = ERROR;
	}
	else if (token->next->type == WORD)
		token->next->type = OUT_FILE;
}

void	ptt_pipe(t_token *token)
{
	if (token->next->type == WORD)
		token->next->type = COMMAND;
}


int8_t ptt_fusonning_double_redir(token_list)
{
	while (token_list)
	{
		if (token_list->type == REDIR_IN)
		{
			if (!ptt_redir_in(token_list))
				return (0);
		}
		else if (token_list->type == REDIR_OUT)
		{
			if (ptt_redir_out(token_list))
				return (0);
		}
		else if (token_list->type == PIPE)
		{
			if (ptt_pipe(token_list))
				return (0);
		}
		token_list = token_list->next;
	}
	return (1);
}

void	ptt_typing_word_token(t_token *token)
{
	if (token->prev->type == START)
		token->type = COMMAND;
	else if (token->prev->type == PIPE)
		token->type = COMMAND;
	else if (token->prev->type == IN_FILE || token->prev->type == OUT_FILE)
		token->type = COMMAND;
	else if (token->prev->type == LIMITER)
		token->type = COMMAND;
	else if (token->prev->type == HEREDOC)
		token->type = LIMITER;
	else if (token->prev->type == REDIR_IN)
		token->type = IN_FILE;
	else if (token->prev->type == REDIR_OUT || token->prev->type == REDIR_APPEND)
		token->type = OUT_FILE;
}

void	ptt_typing_token(t_token *token_list)
{
	ptt_fusonning_double_redir(token_list);
	while (token_list)
	{
		if (token_list->type == WORD)
			ptt_typing_word_token(token_list);
		token_list = token_list->next;
	}
}
