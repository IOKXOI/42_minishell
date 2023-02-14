/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pta_aggregation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 05:07:59 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/14 09:35:46 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int16_t	pta_get_args_number(token_list)
{
	int	args_number;
	
	args_number = 1;
	while (token && token->type != PIPE)
	{
		args_number++;
		token = token->next;
	}
	return (args_number);
}

t_token	*pta_get_node_pipe(t_token *token_list)
{
	while (token && token->type != PIPE)
		token = token->next;
	return (token);
}

t_complete_cmd	*pta_get_cmd(t_token *token_list, t_complete_cmd *cmd_list)
{
	int16_t	args_number;
	t_token	*pipe_node;
	
	args_number = 0;
	args_number = pta_get_args_number(token_list);
	pipe_node = pta_get_node_pipe(token_list);
	while (token_list != pipe_node)
	{
		if (token_list->type == WORD)
		{
			cmd_list->cmd = ft_strjoin(cmd_list->cmd, token_list->value);
			cmd_list->cmd = ft_strjoin(cmd_list->cmd, " ");
		}
		token_list = token_list->next;
	}
}

t_complete_cmd	*pta_aggregation(t_token *token_list)
{
	t_complete_cmd	*cmd_list;

	cmd_list = init_command_list();
	if (!cmd_list)
	{
		free_list(token_list);
		printf("Error: malloc failed in pta_aggregation\n");
		return (NULL);
	}
	while (token_list)
	{
		cmd_list = pta_get_cmd(token_list, cmd_list);
		if (!cmd_list)
		{
			free_list(token_list);
			printf("Error: malloc failed in pta_get_cmd\n");
			return (NULL);
		}
		cmd_list = cmd_list->next;
	}
	
}
	