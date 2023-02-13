/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:17:30 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/13 03:14:24 by sydauria         ###   ########.fr       */
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

void	free_node(t_token *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node->name);
	free(node);
}
