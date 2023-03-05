/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:25:28 by sydauria          #+#    #+#             */
/*   Updated: 2022/12/21 00:30:57 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*first_cmd(char **commands, int *pipefd, t_elements *elements)
{
	int		fd;
	char	*good_commands;

	fd = open(elements->files[0], O_RDONLY);
	if (fd < 0)
	{
		if (*elements->files[0])
			error(elements->files[0], elements);
		else
			error(" ", elements);
	}
	good_commands = try_to_access(commands, elements);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		free(good_commands);
		error("first_cmd: dup2", elements);
	}
	close(fd);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
	{
		free(good_commands);
		error("first_cmd: dup2", elements);
	}
	//close(pipefd[1]);
	//close(pipefd[0]);
	return (good_commands);
}

static char	*last_cmd(char **commands, int *pipefd, t_elements *elements)
{
	int		new_fd;
	char	*good_commands;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		error("last_cmd: dup2", elements);
	new_fd = open(elements->files[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_fd == -1)
		error(elements->files[1], elements);
	good_commands = try_to_access(commands, elements);
	if (dup2(new_fd, STDOUT_FILENO) < 0)
	{
		free(good_commands);
		error("last_cmd: dup2", elements);
	}
	close(pipefd[0]);
	close(new_fd);
	return (good_commands);
}

void	child_process(t_commands *node, char **envp, t_elements *e)
{
	char		*commands;

	if (node == e->first)
		commands = first_cmd(node->commands, e->pipefd, e);
	else
		commands = last_cmd(node->commands, e->pipefd, e);
	if (commands)
	{
		close(e->pipefd[0]);
		close(e->pipefd[1]);
		if (execve(commands, node->commands, envp) == -1)
			error(node->commands[0], e);
	}
	close(e->pipefd[0]);
	close(e->pipefd[1]);
	error_127(e);
}

void	pipe_creator(t_elements *elements)
{
	if (pipe(elements->pipefd) < 0)
		error("on forking : pipe", elements);
}

int	forking(t_elements *elements, char *envp[])
{
	int			i;
	int			ret;
	t_commands	*node;

	i = 0;
	node = elements->first;
	pipe_creator(elements);
	while (node)
	{
		elements->pid_register[i] = fork();
		if (elements->pid_register[i] < 0)
			error("Error on fork", elements);
		else if (elements->pid_register[i] == 0)
			child_process(node, envp, elements);
		else
		{
			close(elements->pipefd[1]);
			node = node->next;
			i++;
		}
	}
	close(elements->pipefd[0]);
	close(elements->pipefd[1]);
	ret = wait_id(elements);
	return (ret);
}
