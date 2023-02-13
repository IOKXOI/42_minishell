/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptt_typing_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:03:17 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/13 03:16:51 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*fusionning two nodes and give a new type*/
t_token	*fusion_node(enum e_type type, t_token *token, t_token *next)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	// if (!new)
	// 	exit_minishell(token);
	new->name = ft_strjoin(token->name, next->name);
	// if (!new->name)
	// 	exit_minishell(token);
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

/*fusionning two nodes redir in to form HERE_DOC*/
t_token	*ptt_redir_in(t_token *token)
{
	if (token->next && token->next->type == REDIR_IN)
		token = fusion_node(HERE_DOC, token, token->next);
	return (token);
}

/*fusionning two nodes redir out to form REDIR_APPEN*/
t_token	*ptt_redir_out(t_token *token)
{
	if (token->next && token->next->type == REDIR_OUT)
		token = fusion_node(REDIR_APPEND, token, token->next);
	return (token);
}

/*loop on list to regroup tokens between them to form an instruction*/
int8_t ptt_fusonning_double_redir(t_token *token)
{
	while (token)
	{
		if (token->type == REDIR_IN)
			token = ptt_redir_in(token);
		else if (token->type == REDIR_OUT)
			token = ptt_redir_out(token);
		token = token->next;
	}
	return (1);
}

/*give a type to a token bylooking precedent token*/
void	ptt_typing_word_token(t_token *token)
{
	enum e_type	v_type;

	v_type = token->prev->type;
	if (v_type == START || v_type == PIPE || v_type == IN_FILE || v_type == OUT_FILE || v_type == LIMITER)
		token->type = CMD;
	else if (v_type == HERE_DOC)
		token->type = LIMITER;
	else if (v_type == REDIR_IN)
		token->type = IN_FILE;
	else if (v_type == REDIR_OUT || v_type == REDIR_APPEND)
		token->type = OUT_FILE;
}

/*loop on the token_list to reconize HERE_DOC and REDIR_APPEN,
then loop on the list to apply the function of giving type to words*/
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
