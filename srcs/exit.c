/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:17:30 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/29 17:26:26 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_list(t_token *list)
{
	t_token	*to_free;
	while (list)
	{
		to_free = list;
		list = list->next;
		free(to_free);
	}
	return (NULL);
}
