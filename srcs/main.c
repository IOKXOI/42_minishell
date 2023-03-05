/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 05:01:04 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/02 19:19:36 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	pt_parse(char *line)
{
	t_token			*token_list;
	t_complete_cmd	*commande;

	token_list = pt_tokenization(line);
	if (!first_check_parse_error(token_list))
		return (pt_free_list(token_list), false);
	ptt_typing_token(token_list);
	p_lexeur(token_list);
	print_all_token(token_list);
	commande = pa_aggregation(token_list);
	print_complete_commande_list(commande);
	free_complete_command_list(commande);
	return (0);
}

int32_t	main(void)
{
	char	*rline;

	rl_outstream = stderr;
	while (1)
	{
		rline = readline(RED "minishell> ");
		if (*rline)
		{
			add_history(rline);
			pt_parse(rline);
		}
		return (0);
	}
	return (0);
}
