/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iok <iok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 06:21:34 by sydauria          #+#    #+#             */
/*   Updated: 2022/11/13 00:47:47 by iok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (paths)
	{
		while (paths[i])
		{
			free(paths[i]);
			i++;
		}
		free(paths[i]);
		free(paths);
	}
}

void	free_files(char **files)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		free(files[i]);
		i++;
	}
	free(files);
}

void	free_list(t_commands *node)
{
	int			i;
	t_commands	*tmp;

	while (node)
	{
		i = 0;
		tmp = node->next;
		if (node->commands)
		{
			while (node->commands[i])
			{
				free(node->commands[i]);
				i++;
			}
			free(node->commands[i]);
			free(node->commands);
		}
		free(node);
		node = tmp;
	}
	free(node);
}

void	free_this_node(t_commands *node, t_elements *elements)
{
	int			i;
	t_commands	*tmp;

	i = 0;
	if (node == elements->first)
		elements->first = node->next;
	else
	{
		tmp = elements->first;
		while (tmp->next != node)
			tmp = tmp->next;
		tmp->next = node->next;
	}
	while (node->commands[i])
	{
		free(node->commands[i]);
		i++;
	}
	free(node->commands[i]);
	free(node->commands);
	free(node);
}
