/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:53:30 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/06 23:13:26 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



// static char	**parse_files(char *argv[], t_elements *elements)
// {
// 	char	**files;

// 	files = malloc(sizeof(char *) * 2);
// 	if (!files)
// 		error("parse_files : malloc", elements);
// 	files[0] = ft_strdup(argv[1]);
// 	if (!files[0])
// 		error("parse_files : ft_strdup", elements);
// 	files[1] = ft_strdup(argv[elements->argc - 1]);
// 	if (!files[1])
// 		error("parse_files : ft_strdup", elements);
// 	return (files);
// }

// static t_commands	*parse_commands(char *argv[], t_elements *elements)
// {
// 	int		i;

// 	i = 2;
// 	if (!ft_strcmp(argv[1], "here_doc"))
// 		i++;
// 	new_node(elements);
// 	elements->first->commands = ft_split(argv[i], ' ');
// 	if (!elements->first->commands)
// 		error("parse_commands : malloc tab on the node", elements);
// 	i++;
// 	while (i < (elements->argc - 1))
// 	{
// 		new_node(elements);
// 		elements->last->commands = ft_split(argv[i], ' ');
// 		if (!elements->last->commands)
// 			error("parse_commands : malloc tab on the node", elements);
// 		i++;
// 	}
// 	return (elements->first);
// }

void	init_struct(char *env[], t_monitor monitor, t_elements *elements)
{
	elements->paths = NULL;
	monitor->pid_register = NULL;
	elements->paths = parse_paths(env, elements);
	monitor->pid_register = init_pid_register(argc, elements);
}
