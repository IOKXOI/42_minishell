/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 05:31:21 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/01 05:38:04 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	new_node(t_elements *elements)
{
	if (!elements->first)
	{
		elements->first = malloc(sizeof(t_commands));
		if (!elements->first)
			error("malloc in new_node", elements);
		elements->first->next = NULL;
		elements->last = elements->first;
	}
	else
	{
		elements->last->next = malloc(sizeof(t_commands));
		if (!elements->last->next)
		{
			error("malloc in new_node", elements);
			free_list(elements->first);
		}
		elements->last = elements->last->next;
		elements->last->next = NULL;
	}
}
