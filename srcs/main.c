/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 05:01:04 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/08 07:14:51 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*pt_extraction_from_line(int32_t n, char *original)
{
	int16_t		i;
	char		*new_line;

	i = 0;
	new_line = malloc(sizeof(char) * n + 2);
	if (!new_line)
		return (NULL);
	while (i <= n)
	{
		new_line[i] = original[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

bool	pt_parse(char *line)
{
	t_token	*token_list;

	token_list = pt_tokenization(line);
	ptt_typing_token(token_list);
	print_all_token(token_list);
	pt_free_list(token_list->first);
	return (0);
}

int32_t	main(void)
{
	char	*rline;

	rl_outstream = stderr;
	while (1)
	{
		rline = readline(RED "minishell> ");
		add_history(rline);
		pt_parse(rline);
	}
	return (0);
}
