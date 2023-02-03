/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tokenisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:06:56 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/03 21:20:16 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	get_token(int32_t offset_in_line, char *line, t_token *token_node)
{
	token_node->type = is_special(line[offset_in_line]);
	if (token_node->type == QUOTES)
		return (full_quote(offset_in_line, line, token_node));
	else if (token_node->type)
		return (ft_strlen(get_special(offset_in_line, line, token_node)));
	else
		token_node->name = extraction_from_line(offset_in_line, line);
	if (!token_node->name || offset_in_line < 0)
	{
		ERR
		exit(EXIT_FAILURE);
	}
	return (1);
}

char	*token_extracting(char *line, t_token *token)
{
	int16_t		offset_in_line;
	char		*remainder;
	
	offset_in_line = skip_until_special_is_next(line);
	if (is_space(line[offset_in_line]))
		offset_in_line += skip_spaces(line + offset_in_line);
	offset_in_line += get_token(offset_in_line ,line, token);
	remainder = ft_strdup(line + offset_in_line);
	free(line);
	return (remainder);
}

t_token	*tokenization(char *line)
{
	t_token		*token_list;

	token_list = init_node();
	while (*line)
	{
		line = token_extracting(line, token_list);
		if (!line)
		{
			free_list(token_list->first);
			exit (1);
		}
		printf(RED "After extract ."YLW"%s"RED".from line, remainder is: ."YLW"%s.\n" WHT, token_list->name, line);//-
		token_list->next = create_new_node(token_list);
		token_list = token_list->next;
	}
	return (token_list->first);
}
