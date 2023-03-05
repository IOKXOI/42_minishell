/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:21:19 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/02 19:59:23 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <minishell.h>
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_complete_cmd	*commande_list;

	while(true)
	{
		//line = expand();
		commande_list = parsing(line);
		execution(env, commande_list);
	}
	return (0);
}
