/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_aggregation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 05:07:59 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/15 02:10:50 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*fill **args in complete_commande struct, leaving index 0 for commande*/
static void	pa_fill_args(t_complete_cmd *cmd, char *name)
{
	uint32_t	empty_args;

	empty_args = 1;
	while (cmd->args[empty_args] != NULL)
		empty_args++;
	cmd->args[empty_args] = name;
}

static void	pa_fill_infile(t_complete_cmd *cmd, char *name)
{
	uint32_t	empty_infile;

	empty_infile = 0;
	while (cmd->infile[empty_infile] != NULL)
		empty_infile++;
	cmd->infile[empty_infile] = name;
}

static void	pa_fill_outfile(t_complete_cmd *cmd, char *name)
{
	uint32_t	empty_outfile;

	empty_outfile = 0;
	while (cmd->outfile[empty_outfile] != NULL)
		empty_outfile++;
	cmd->outfile[empty_outfile] = name;
}

static void	pa_fill_outfile_append(t_complete_cmd *cmd, char *name)
{
	uint32_t	empty_outfile_append;

	empty_outfile_append = 0;
	while (cmd->outfile_append[empty_outfile_append] != NULL)
		empty_outfile_append++;
	cmd->outfile_append[empty_outfile_append] = name;
}

static void	pa_fill_here_doc(t_complete_cmd *cmd, char *name)
{
	uint32_t	empty_here_doc;

	empty_here_doc = 0;
	while (cmd->limiter[empty_here_doc] != NULL)
		empty_here_doc++;
	cmd->limiter[empty_here_doc] = name;
}


static void	pa_token_traitment(t_token *token, t_complete_cmd *cmd)
{
	if (token->type == WORD)
		pa_fill_args(cmd, token->name);
	else if (token->type == CMD)
	{
		cmd->commande = token->name;
		cmd->args[0] = token->name;
	}
	else if (token->type == IN_FILE)
		pa_fill_infile(cmd, token->name);
	else if (token->type == OUT_FILE)
		pa_fill_outfile(cmd, token->name);
	else if (token->type == OUT_FILE_APPEND)
		pa_fill_outfile_append(cmd, token->name);
	else if (token->type == LIMITER)
		pa_fill_here_doc(cmd, token->name);
}


t_token	*pa_fill_compete_cmd_node(t_token *token_start, t_complete_cmd *cmd)
{
	while (token_start->type != END && token_start->type != PIPE)
	{
		pa_token_traitment(token_start, cmd);
		token_start = token_start->next;
	}
	return(pa_free_used_token(token_start));
}

t_complete_cmd	*pa_aggregation(t_token *token_list_section)
{
	t_complete_cmd	*complete_cmd_list;
	complete_cmd_list = init_command_list(token_list_section->first);
	if (!complete_cmd_list)
		return (NULL);
	while (token_list_section)
	{
		print_all_token(token_list_section->first);
		printf("==============\n");
		if (!set_malloc_complete_cmd(token_list_section->first, complete_cmd_list))
			return (NULL);
		token_list_section = pa_fill_compete_cmd_node(token_list_section->first, complete_cmd_list);
		if (!token_list_section)
			break;
		complete_cmd_list = new_complete_cmd(complete_cmd_list);
		// if (!complete_cmd_list)
		// {
		// 	pt_free_list(token_list_section);
		// 	printf("Error: malloc failed in pta_get_cmd\n");
		// 	return (NULL);
		// }
	}
	return (complete_cmd_list->first);
}
