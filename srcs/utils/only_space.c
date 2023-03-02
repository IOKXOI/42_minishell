/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:05:22 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/25 23:55:38 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	only_space(t_token *token)
{
	if (token->type == START || token->type == END)
		return (false);
	if (token->type == SPACE_BIS)
		return (true);
	else
		return (false);
}
