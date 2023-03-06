/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_linked_list_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:40:53 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/02 00:37:55 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	malloc_and_init_args(t_complete_cmd *cmd)
{
	uint32_t	i;

	i = 0;
	cmd->args = malloc(sizeof(char *) * (cmd->args_number + 1));
	if (cmd->args == NULL)
		exit(EXIT_FAILURE);
	while (i <= cmd->args_number)
	{
		cmd->args[i] = NULL;
		i++;
	}
}

void	malloc_and_init_infile(t_complete_cmd *cmd)
{
	uint32_t	i;

	i = 0;
	cmd->infile = malloc(sizeof(char *) * (cmd->infile_number + 1));
	if (cmd->infile == NULL)
		exit(EXIT_FAILURE);
	while (i <= cmd->infile_number)
	{
		cmd->infile[i] = NULL;
		i++;
	}
}

void	malloc_and_init_outfile(t_complete_cmd *cmd)
{
	uint32_t	i;

	i = 0;
	cmd->outfile = malloc(sizeof(char *) * (cmd->outfile_number + 1));
	if (cmd->outfile == NULL)
		exit(EXIT_FAILURE);
	while (i <= cmd->outfile_number)
	{
		cmd->outfile[i] = NULL;
		i++;
	}
}

void	malloc_and_init_outfile_append(t_complete_cmd *cmd)
{
	uint32_t	i;

	i = 0;
	cmd->outfile_append = malloc(sizeof(char *) * (cmd->outfile_append_number + 1));
	if (cmd->outfile_append == NULL)
		exit(EXIT_FAILURE);
	while (i <= cmd->outfile_append_number)
	{
		cmd->outfile_append[i] = NULL;
		i++;
	}
}

void	malloc_and_init_limiter(t_complete_cmd *cmd)
{
	uint32_t	i;

	i = 0;
	cmd->limiter = malloc(sizeof(char *) * (cmd->here_doc_number + 1));
	if (cmd->limiter == NULL)
		exit(EXIT_FAILURE);
	while (i <= cmd->here_doc_number)
	{
		cmd->limiter[i] = NULL;
		i++;
	}
}
