/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:25:28 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/05 23:11:02 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*first_cmd(char **commands, int *pipefd, t_elements *elements)
{
	int		fd;
	char	*good_commands;

	open_infile(elements);
	open_outfile(elements);
	open_outfile_append(elements);
	good_commands = try_to_access(commands, elements);
	return (good_commands);
}

static char	*last_cmd(char **commands, int *pipefd, t_elements *elements)
{
	int		new_fd;
	char	*good_commands;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		error("last_cmd: dup2", elements);
	new_fd = open(elements->outfile[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void	child_process(char **envp, s_complete_cmd *e)
{
	char		*commands;

	if (&e == e->first)
		commands = first_cmd(e->args, e->pipefd, e);
	else if (&e == e->last)
		commands = last_cmd(e->args, e->pipefd, e);
	else
		commands = intermediate_cmd(e->args, e->pipefd, e);
	if (commands)
	{
		close(e->pipefd[0]);
		close(e->pipefd[1]);
		if (execve(commands, e->args, envp) == -1)
			error(e->args[0], e);
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

int	forking(s_complete_cmd *elements, char *envp[])
{
	int			i;
	int			ret;

	i = 0;
	pipe_creator(elements);
	while (elements)
	{
		elements->pid_register[i] = fork();
		if (elements->pid_register[i] < 0)
			error("Error on fork", elements);
		else if (elements->pid_register[i] == 0)
			child_process(envp, elements);
		else
		{
			close(elements->pipefd[1]);
			elements = elements->next;
			i++;
		}
	}
	close(elements->pipefd[0]);
	close(elements->pipefd[1]);
	ret = wait_id(elements);
	return (ret);
}


void	open_infile(t_complete_cmd *elements)
{
	int		fd;
	uint_32	i;

	i = 0;
	fd = STDIN_FILENO;
	while (elements->infile[i])
	{
		fd = open(elements->infile[i], O_RDONLY);
		if (fd < 0)
		{
			if (*elements->infile[i])
				error(elements->infile[i], elements);
			else
				error(" ", elements);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
			error("open_infile: dup2", elements);
		close(fd);
		i++;
	}
}

void	open_outfile(t_complete_cmd *elements)
{
	int		fd;
	uint_32	i;

	i = 0;
	fd = STDOUT_FILENO;
	while (elements->outfile[i])
	{
		fd = open(elements->outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			error(elements->outfile[i], elements);
		if (dup2(fd, STDOUT_FILENO) < 0)
			error("open_outfile: dup2", elements);
		close(fd);
		i++;
	}
}

void	open_outfile_append(t_complete_cmd *elements)
{
	int		fd;
	uint_32	i;

	i = 0;
	fd = STDOUT_FILENO;
	while (elements->outfile_append[i])
	{
		fd = open(elements->outfile[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			error(elements->outfile[i], elements);
		if (dup2(fd, STDOUT_FILENO) < 0)
			error("open_outfile_append: dup2", elements);
		close(fd);
		i++;
	}
}

