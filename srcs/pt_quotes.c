/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 08:56:16 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/04 01:17:40 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int16_t	pt_is_quote(int8_t charater)
{
	if (charater == '\'')
		return (QUOTE);
	if (charater == '"')
		return (QUOTES);
	if (charater == '`')
		return (GRAVE_QUOTE);
	return (0);
}

char	*pt_get_quoting(int16_t quote_type, char *quote_start)
{
	int16_t		offset_in_quote;
	char		*token;

	offset_in_quote = 1;
	while (quote_start[offset_in_quote] \
		&& ((pt_is_quote(quote_start[offset_in_quote]) != quote_type)))
		offset_in_quote++;
	token = pt_extraction_from_line(offset_in_quote, quote_start);
	return (token);
}

int32_t	pt_full_quote(int32_t offset_in_line, char *line, t_token *token_node)
{
	int16_t		quote_type;

	quote_type = pt_is_quote(line[offset_in_line]);
	token_node->name = pt_get_quoting(quote_type, line + offset_in_line);
	if (token_node->name == NULL)
	{
		pt_free_list(token_node->first);
		free(line);
		printf("Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	return (offset_in_line += ft_strlen(token_node->name));
}
