/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tokenisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:06:56 by sydauria          #+#    #+#             */
/*   Updated: 2023/03/02 05:44:51 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*copy a snippet of the line on the other one*/
char	*pt_extraction_from_line(int32_t n, char *original)
{
	int32_t		i;
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

int32_t	pt_get_token(int32_t offset_in_line, char *line, t_token *token_node)
{
	token_node->type = pt_is_special(line[offset_in_line]);
	if (token_node->type == SPACE_BIS)
	{
		token_node->name = NULL;
		return (1);
	}
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
	int32_t		offset_in_line;
	char		*remainder;

	offset_in_line = pt_skip_until_special_is_next(line);
	offset_in_line += pt_get_token(offset_in_line, line, token);
	// if (!line[offset_in_line + 1])
	// {
	// 	return (ft_strdup(""));
	// }
	remainder = ft_strndup(line + offset_in_line, ft_strlen(line + offset_in_line));
	free(line);
	return (remainder);
}

t_token	*pt_tokenization(char *line)
{
	t_token		*token_list;

	token_list = pt_init_node();
	token_list->next = pt_create_new_node(token_list);
	token_list = token_list->next;
	while (*line)
	{
		line = pt_token_extracting(line, token_list);
		if (!line)
		{
			pt_free_list(token_list->first);
			exit (1);
		}
		else
		{
			token_list->next = pt_create_new_node(token_list);
			token_list = token_list->next;
		}
		token_list->name = NULL;
	}
	token_list->type = END;
	free(line);
	return (token_list->first);
}
