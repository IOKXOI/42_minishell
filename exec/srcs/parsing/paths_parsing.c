/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:53:30 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/02 20:00:26 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_paths(char **paths, t_elements *elements)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		if (!paths[i])
			error("parse_paths : ft_strjoin", elements);
		free(tmp);
		i++;
	}
	return (paths);
}

static char	**parse_paths(char *envp[], t_elements *elements)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] && ((envp[i][0] != 'P') || (envp[i][1] != 'A')
		|| (envp[i][2] != 'T') || (envp[i][3] != 'H') || (envp[i][4] != '=')))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		error("parse_paths : ft_split", elements);
	paths = get_paths(paths, elements);
	return (paths);
}

static char	**parse_files(char *argv[], t_elements *elements)
{
	char	**files;

	files = malloc(sizeof(char *) * 2);
	if (!files)
		error("parse_files : malloc", elements);
	files[0] = ft_strdup(argv[1]);
	if (!files[0])
		error("parse_files : ft_strdup", elements);
	files[1] = ft_strdup(argv[elements->argc - 1]);
	if (!files[1])
		error("parse_files : ft_strdup", elements);
	return (files);
}

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

void	init_struct(int argc, char *argv[], char *env[], t_elements *elements)
{
	elements->paths = NULL;
	elements->pid_register = NULL;
	elements->paths = parse_paths(env, elements);
	elements->pid_register = init_pid_register(argc, elements);
}
