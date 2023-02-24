/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:17:30 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/24 00:44:40 by sydauria         ###   ########.fr       */
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
	node->prev->next = node->next;
	node->next->prev = node->prev;
	next = node->next;
	free(node->name);
	free(node);
	return (next);
}

void	free_complete_command_list(t_complete_cmd *complete_commande)
{
	if (complete_commande->commande)
		free(complete_commande->commande);
	while (complete_commande->args)
		free(complete_commande->args++);
	while (complete_commande->infile)
		free(complete_commande->infile++);
	while (complete_commande->outfile)
		free(complete_commande->outfile++);
	while (complete_commande->outfile_append)
		free(complete_commande->outfile_append++);
	while (complete_commande->limiter)
		free(complete_commande->limiter++);
}
