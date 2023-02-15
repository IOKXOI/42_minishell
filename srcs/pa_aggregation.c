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

static void	pa_fill_args(t_complete_cmd *cmd, char *name)
{
	int16_t	i;
	
	i = 0;
	printf("token name = %s, cmd_->args%p \n", name, cmd->args);
	while (cmd->args[i])
		i++;
	cmd->args[i] = name;
}

static void	pa_token_traitment(t_token *token, t_complete_cmd *cmd)
{
	if (token->type == WORD)
		pa_fill_args(cmd, token->name);
	else if (token->type == CMD)
		cmd->commande = token->name;
	else if (token->type == REDIR_IN)
		cmd->infile = token->name;
	else if (token->type == REDIR_OUT)
		cmd->outfile = token->name;
	else if (token->type == REDIR_APPEND)
		cmd->outfile_append = token->name;
	else if (token->type == LIMITER)
		cmd->limiter = token->name;
	free(token);
}

int16_t	pa_get_args_number(t_token *token_list)
{
	int	args_number;
	
	args_number = 0;
	while (token_list && token_list->type != PIPE)
	{
		if (token_list->type == CMD || token_list->type == WORD)
			args_number++;
		token_list = token_list->next;
	}
	return (args_number);
}

t_token	*pa_get_cmd(t_token *token_start, t_complete_cmd *cmd)
{
	int16_t	args_number;
	t_token	*token;
	
	token = token_start->next;
	cmd->args_nb = pa_get_args_number(token_start);
	printf("args_number = %d\n", args_number);
	cmd->args = malloc(sizeof(char *) * (cmd->args_nb + 1));
	// if (!cmd->cmd)
	// 	return (NULL);
	cmd->args[args_number] = NULL;
	while (token->type != END && token->type != PIPE)
	{
		pa_token_traitment(token, cmd);
		token = token->next;
	}
	return (token_list_first);
}

t_complete_cmd	*pa_aggregation(t_token *token_list)
{
	t_complete_cmd	*complete_cmd_list;

	complete_cmd_list = init_command_list();
	if (!complete_cmd_list)
	{
		pt_free_list(token_list);
		printf("Error: malloc failed in pta_aggregation\n");
		return (NULL);
	}
	while (token_list)
	{
		token_list = pa_get_cmd(token_list->first, complete_cmd_list);
		complete_cmd_list = new_complete_cmd(complete_cmd_list);
		if (!complete_cmd_list)
		{
			pt_free_list(token_list);
			printf("Error: malloc failed in pta_get_cmd\n");
			return (NULL);
		}
	}
	return (complete_cmd_list);
}
	