/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:55:45 by sydauria          #+#    #+#             */
/*   Updated: 2022/11/24 06:08:55 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str, t_elements *elements)
{
	if (*str)
		perror(str);
	if (elements->paths)
		free_paths(elements->paths);
	if (elements->first)
		free_list(elements->first);
	if (elements->files)
		free_files(elements->files);
	if (elements->here_doc)
		free(elements->here_doc);
	if (elements->pid_register)
		free(elements->pid_register);
	exit(EXIT_FAILURE);
}

void	error_printf(char *str, t_elements *elements)
{
	ft_printf("%s\n", str);
	if (elements->paths)
		free_paths(elements->paths);
	if (elements->first)
		free_list(elements->first);
	if (elements->files)
		free_files(elements->files);
	if (elements->here_doc)
		free(elements->here_doc);
	if (elements->pid_register)
		free(elements->pid_register);
	exit(EXIT_FAILURE);
}

void	error_127(t_elements *elements)
{
	if (elements->paths)
		free_paths(elements->paths);
	if (elements->first)
		free_list(elements->first);
	if (elements->files)
		free_files(elements->files);
	if (elements->here_doc)
		free(elements->here_doc);
	if (elements->pid_register)
		free(elements->pid_register);
	exit(127);
}

void	error_empty_cmd(char *cmd, t_elements *elements)
{
	ft_printf("%s: command not found", cmd);
	if (elements->paths)
		free_paths(elements->paths);
	if (elements->first)
		free_list(elements->first);
	if (elements->files)
		free_files(elements->files);
	if (elements->here_doc)
		free(elements->here_doc);
	if (elements->pid_register)
		free(elements->pid_register);
	exit(EXIT_FAILURE);
}

void	error_directory(char *cmd, t_elements *elements)
{
	ft_printf("%s: Is a directory\n", cmd);
	if (elements->paths)
		free_paths(elements->paths);
	if (elements->first)
		free_list(elements->first);
	if (elements->files)
		free_files(elements->files);
	if (elements->here_doc)
		free(elements->here_doc);
	if (elements->pid_register)
		free(elements->pid_register);
	exit(EXIT_FAILURE);
}
/*
void	error_no_file(char *cmd, t_elements *elements)
{
	ft_printf("%s: command not found", cmd);
	if (elements->paths)
		free_paths(elements->paths);
	if (elements->first)
		free_list(elements->first);
	if (elements->files)
		free_files(elements->files);
	if (elements->here_doc)
		free(elements->here_doc);
	if (elements->pid_register)
		free(elements->pid_register);
	exit(EXIT_FAILURE);
*/
