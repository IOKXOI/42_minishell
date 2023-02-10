/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_linked_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:06:14 by sydauria          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/08 10:37:18 by sydauria         ###   ########.fr       */
=======
/*   Updated: 2023/02/08 10:15:40 by sydauria         ###   ########.fr       */
>>>>>>> a618296f299fe7bfecea2710cc4d1bc174e0ce71
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*pt_init_node(void)
{
	t_token	*first_node;

	first_node = malloc(sizeof(t_token));
	if (!first_node)
		return (NULL);
	first_node->type = START;
<<<<<<< HEAD
	first_node->name = ft_strdup("START");
=======
	first_node->name = NULL;
>>>>>>> a618296f299fe7bfecea2710cc4d1bc174e0ce71
	first_node->first = first_node;
	first_node->prev = NULL;
	first_node->next = NULL;
	return (first_node);
}

t_token	*pt_create_new_node(t_token *existing_node)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		pt_free_list(existing_node->first);
		return (NULL);
	}
	existing_node->next = new_node;
	new_node->first = existing_node->first;
	new_node->prev = existing_node;
	new_node->next = NULL;
	return (new_node);
}
