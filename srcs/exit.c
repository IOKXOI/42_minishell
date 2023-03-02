/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:17:30 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/02 02:17:11 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*pt_free_list(t_token *list)
{
	t_token	*to_free;

	while (list)
	{
		to_free = list;
		free(list->name);
		list = list->next;
		free(to_free);
	}
	return (NULL);
}

t_token	*free_node(t_token *node)
{
	t_token	*next;

	next = node->next;
	node->prev->next = next;
	node->next->prev = node->prev;
	free(node->name);
	free(node);
	return (next);
}

t_token	*delete_used_token(t_token *token)
{
	t_token	*next;

	if (token->type == START)
		return (token->next);
	else if (token->type == END)
	{
		free(token->first);
		free(token);
		return (NULL);
	}
	else
	{
		next = token->next;
		next->prev = token->prev;
		token->prev->next = next;
		if (token->type == REDIR_APPEND || token->type == REDIR_IN || token->type == REDIR_OUT || token->type == HERE_DOC)
			free(token->name);
		free(token);
		return (next);
	}
}

void	free_complete_command_node(t_complete_cmd *complete_commande)
{
	uint32_t	i;

	i = 0;
	while (complete_commande->args[i])
		free(complete_commande->args[i++]);
	free(complete_commande->args);
	i = 0;
	while (complete_commande->infile[i])
		free(complete_commande->infile[i++]);
	free(complete_commande->infile);
	i = 0;
	while (complete_commande->outfile[i])
		free(complete_commande->outfile[i++]);
	free(complete_commande->outfile);
	i = 0;
	while (complete_commande->outfile_append[i])
		free(complete_commande->outfile_append[i++]);
	free(complete_commande->outfile_append);
	i = 0;
	while (complete_commande->limiter[i])
		free(complete_commande->limiter[i++]);
	free(complete_commande->limiter);
}

void	free_complete_command_list(t_complete_cmd *complete_commande)
{
	t_complete_cmd	*tmp;

	while (complete_commande)
	{
		tmp = complete_commande->next;
		free_complete_command_node(complete_commande);
		free(complete_commande);
		complete_commande = tmp;
	}
}
