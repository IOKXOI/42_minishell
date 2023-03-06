/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_linked_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:06:14 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/06 23:03:35 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*pt_init_node(void)
{
	t_token	*first_node;

	first_node = malloc(sizeof(t_token));
	if (!first_node)
		return (NULL);
	first_node->type = START;
	first_node->name = NULL;
	first_node->first = first_node;
	first_node->prev = NULL;
	first_node->next = NULL;
	return (first_node);
}

t_token	*pt_create_new_node(t_token *existing_node)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		pt_free_list(existing_node->first);
		return (NULL);
	}
	existing_node->next = new_node;
	new_node->first = existing_node->first;
	new_node->prev = existing_node;
	new_node->next = NULL;
	return (new_node);
}

t_complete_cmd	*init_command_list(t_token *token_list_start, t_monitor *monitor)
{
	t_complete_cmd	*cmd_list;

	cmd_list = malloc(sizeof(t_complete_cmd));
	if (!cmd_list)
		return (pt_free_list(token_list_start), NULL);
	cmd_list->first = cmd_list;
	cmd_list->prev = NULL;
	cmd_list->next = NULL;
	cmd_list->commande = NULL;
	cmd_list->infile = NULL;
	cmd_list->outfile = NULL;
	cmd_list->outfile_append = NULL;
	cmd_list->limiter = NULL;
	cmd_list->args = NULL;
	cmd_list->monitor = monitor;
	return (cmd_list);
}

t_complete_cmd	*new_complete_cmd(t_complete_cmd *cmd_list)
{
	t_complete_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_complete_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->first = cmd_list->first;
	new_cmd->prev = cmd_list;
	new_cmd->next = NULL;
	cmd_list->next = new_cmd;
	new_cmd->commande = NULL;
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->outfile_append = NULL;
	new_cmd->limiter = NULL;
	new_cmd->args = NULL;
	return (new_cmd);
}

t_token	*pa_free_used_token(t_token *token)
{
	t_token	*tmp;
	t_token	*separator;

	separator = token->next;
	if (token->type == END)
	{
		free(token->first);
		free(token);
		return (NULL);
	}
	else
	{
		while (token->type != START)
		{
			tmp = token->prev;
			free(token);
			token = tmp;
		}
		token->first->next = separator;
		separator->prev = token->first;
		return (token->first);
	}
}
