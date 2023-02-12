/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_special.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:18:10 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/13 00:43:51 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pt_is_space(int8_t character)
{
	if ((character >= 9 && character <= 13) || character == 32)
		return (1);
	return (0);
}

enum e_type	pt_is_special(int8_t character)
{
	if (pt_is_space(character))
		return (SPACE_BIS);
	else if (character == '<')
		return (REDIR_IN);
	else if (character == '>')
		return (REDIR_OUT);
	else if (character == '|')
		return (PIPE);
	else if (character == '\'')
		return (SINGLE_Q);
	else if (character == '"')
		return (DOUBLE_Q);
	return (0);
}

char	*get_special(int32_t offsett_in_line, char *line, t_token *token_node)
{
	token_node->name = pt_extraction_from_line(offsett_in_line, line);
	if (!token_node->name)
	{
		pt_free_list(token_node->first);
		free(line);
		printf("Error: malloc failed\n");
		return (NULL);
	}
	return (token_node->name);
}

int16_t	pt_skip_until_special_is_next(char *line)
{
	int16_t	offset_in_line;

	offset_in_line = 0;
	if (pt_is_special(line [offset_in_line]))
		return (offset_in_line);
	while (line[offset_in_line] && !pt_is_special(line[offset_in_line + 1]))
		offset_in_line++;
	if (!line[offset_in_line])
		return (offset_in_line - 1);
	return (offset_in_line);
}

void	clean_spaces_nodes(t_token *token)
{
	while (token)
	{
		if (token->type == SPACE_BIS)
		{
			free_node(token);
			token = token->next;
		}
	}
}
