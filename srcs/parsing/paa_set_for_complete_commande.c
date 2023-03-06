/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paa_set_for_complete_commande.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:46:18 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/21 13:49:17 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Get how much unit i need to malloc for each type in a section on the rline*/
static void	count_for_malloc_complete_commande(t_complete_cmd *cmd, t_token *token)
{
	cmd->args_number = 0;
	cmd->infile_number = 0;
	cmd->outfile_number = 0;
	cmd->outfile_append_number = 0;
	cmd->here_doc_number = 0;
	while (token->type != END && token->type != PIPE)
	{
		if (token->type == CMD || token->type == WORD)
			cmd->args_number++;
		else if (token->type == IN_FILE)
			cmd->infile_number++;
		else if (token->type == OUT_FILE)
			cmd->outfile_number++;
		else if (token->type == OUT_FILE_APPEND)
			cmd->outfile_append_number++;
		else if (token->type == LIMITER)
			cmd->here_doc_number++;
		token = token->next;
	}
}

/*Init malloc for every tab in complete_commande struct*/
bool	set_malloc_complete_cmd(t_token *token, t_complete_cmd *cmd)
{
	count_for_malloc_complete_commande(cmd, token);
	malloc_and_init_args(cmd);
	malloc_and_init_infile(cmd);
	malloc_and_init_outfile(cmd);
	malloc_and_init_outfile_append(cmd);
	malloc_and_init_limiter(cmd);
	return (true);
}
