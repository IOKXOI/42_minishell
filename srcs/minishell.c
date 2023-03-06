/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:21:19 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/07 00:03:29 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static char	**get_paths(char **paths, t_monitor *monitor)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		if (!paths[i])
			error("parse_paths : ft_strjoin", monitor);
		free(tmp);
		i++;
	}
	return (paths);
}

static char	**parse_paths(char *envp[], t_monitor *monitor)
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
		error("parse_paths : ft_split", monitor);
	paths = get_paths(paths, monitor);
	return (paths);
}

void	init_monitor(char **env, t_complete_cmd *commande_list, t_monitor *monitor)
{
	monitor->pipe_number = 0;
	while (commande_list)
	{
		monitor->pipe_number++;
		commande_list = commande_list->next;
	}
	monitor->paths = parse_paths(env, monitor);
}

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
