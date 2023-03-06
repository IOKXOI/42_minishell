/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:38:20 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/06 20:46:32 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	*init_pid_register(int pipe_number)
{
	int	*pid_register;

	pid_register = malloc(sizeof(int) * pipe_number);
	if (!pid_register)
		error("Malloc: impossible to create pid_register", elements);
	return (pid_register);
}

int	wait_id(int pipe_nummber, t_monitor *monitor)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipe_number)
	{
		waitpid(monitor->pid_register[i], &status, 0);
		i++;
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
