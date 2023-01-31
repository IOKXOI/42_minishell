/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:06:14 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/26 15:55:37 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_node()
{
	t_token	*first_node;

	first_node = malloc(sizeof(t_token));
	if (!first_node)
	{
		ERR
		printf(RED"first_node fail\n"WHT);//-
		exit(EXIT_FAILURE);
	}
	first_node->name = "100"; //-
	first_node->token = 100; //-
	first_node->first = first_node;
	first_node->prev = NULL;
	first_node->next = NULL;
	printf(RED"first_node create\n"WHT);//-
	return (first_node);
}

t_token	*create_new_node(t_token *existing_node)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		ERR
		printf(RED"new_node fail\n"WHT);//-
		exit(EXIT_FAILURE);
	}
	existing_node->next = new_node;
	new_node->name = "100"; //-
	new_node->token = 100; //-
	new_node->first = existing_node->first;
	new_node->prev = existing_node;
	new_node->next = NULL;
	printf(RED"new_node create\n"WHT);//-
	return (new_node);
}
