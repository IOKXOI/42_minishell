/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:36:39 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/09 13:56:39 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*item;
	t_list	*next_item;

	item = *lst;
	while (item)
	{
		next_item = item->next;
		ft_lstdelone(item, del);
		item = next_item;
	}
	*lst = NULL;
}
