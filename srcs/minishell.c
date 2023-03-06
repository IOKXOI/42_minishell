/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:21:19 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/06 23:16:45 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_complete_cmd	*commande_list;
	t_monitor		monitor;

	//env = update_SHLVL(env);
	while(true)
	{
		//line = expand(***env);
		commande_list = pt_parse(line, &monitor);
		init_monitor(env, commande_list, &monitor);
		execution(env, commande_list);
	}
	return (0);
}

void	init_monitor(char **env, t_complete_cmd *commande_list, t_monitor *monitor)
{
	monitor->pipe_number = 0;
	while (commande_list)
	{
		monitor->pipe_number++;
		commande_list = commande_list->next;
	}
	monitor->paths = get_paths(env, monitor);
}

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
