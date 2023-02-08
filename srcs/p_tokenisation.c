/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tokenisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:06:56 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/08 06:37:36 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	pt_get_token(int32_t offset_in_line, char *line, t_token *token_node)
{
	token_node->type = pt_is_special(line[offset_in_line]);
//	if (token_node->type == QUOTES)
//		return (pt_full_quote(offset_in_line, line, token_node));
	if (token_node->type == SPACE_BIS)
		return (1);
	else if (token_node->type)
		return (ft_strlen(get_special(offset_in_line, line, token_node)));
	else
		token_node->name = pt_extraction_from_line(offset_in_line, line);
	if (!token_node->name || offset_in_line < 0)
		exit(EXIT_FAILURE);
	return (1);
}

char	*pt_token_extracting(char *line, t_token *token)
{
	int16_t		offset_in_line;
	char		*remainder;

	offset_in_line = pt_skip_until_special_is_next(line);
	//if (pt_is_space(line[offset_in_line]))
	//	offset_in_line += pt_skip_spaces(line + offset_in_line);
	offset_in_line += pt_get_token(offset_in_line, line, token);
	remainder = ft_strdup(line + offset_in_line);
	free(line);
	return (remainder);
}

t_token	*pt_tokenization(char *line)
{
	t_token		*token_list;

	token_list = pt_init_node();
	token_list = token_list->next;
	while (*line)
	{
		line = pt_token_extracting(line, token_list);
		if (!line)
		{
			pt_free_list(token_list->first);
			exit (1);
		}
		else if (*line && token_list->name)
		{
			token_list->next = pt_create_new_node(token_list);
			token_list = token_list->next;
		}
	}
	return (token_list->first);
}
