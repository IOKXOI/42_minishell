/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 08:56:16 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/21 15:54:50 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int8_t	pt_is_quote(int8_t charater)
{
	if (charater == '\'')
		return (SINGLE_Q);
	if (charater == '"')
		return (DOUBLE_Q);
	return (0);
}

// bool	next_is_not_quote(char *quote_start, int32_t offset_in_quote)
// {
// 	if (quote_start[offset_in_quote] == '\\')
// 	{
// 		if (quote_start[offset_in_quote + 1] == '\0')
// 			return (false);
// 		if (quote_start[offset_in_quote + 1] == '\'')
// 			return (false);
// 		if (quote_start[offset_in_quote + 1] == '"')
// 			return (false);
// 	}
// 	return (true);
// }

int32_t	pt_get_next_quote(int16_t quote_type, char *quote_start)
{
	int32_t		offset_in_quote;

	offset_in_quote = 1;
	while (quote_start[offset_in_quote] \
		&& ((pt_is_quote(quote_start[offset_in_quote]) != quote_type)))
		offset_in_quote++;
	return (offset_in_quote);
}

int32_t	pt_full_quote(int32_t offset_in_line, char *line, t_token *token_node)
{
	int16_t		quote_type;

	quote_type = pt_is_quote(line[offset_in_line]);
	if (token_node->name == NULL)
	{
		pt_free_list(token_node->first);
		free(line);
		printf("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	return (offset_in_line += ft_strlen(token_node->name));
}
