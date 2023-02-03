/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 05:01:04 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/03 21:36:22 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_space(int8_t character)
{
	if ((character >= 9 && character <= 13) || character == 32)
		return (1);
	return (0);
}

int16_t	is_special(int8_t character)
{
	if (is_space(character))
		return(SPACE_BIS);
	if (character == '<')
		return (IN_FILE);
	if (character == '>')
		return (OUT_FILE);
	if (character == '|')
		return (PIPE);
	if (character == '\'' || character == '"')
		return (QUOTES);
	return (0);
}

char	*get_special(int32_t offsett_in_line, char *line, t_token *token_node)
{
	token_node->name = ft_strndup(line, offsett_in_line);
	if (!token_node->name)
	{
		free_list(token_node->first);
		free(line);
		printf("Error: malloc failed");
		return (NULL);
	}
	return (token_node->name);
}

char	*extraction_from_line(int32_t n, char *original)
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

int16_t	skip_until_special_is_next(char *line)
{
	int16_t	offset_in_line;

	offset_in_line = 0;
	if (is_special(line [offset_in_line]))
		return (offset_in_line);
	while (line[offset_in_line] && !is_special(line[offset_in_line + 1]))
		offset_in_line++;
	return (offset_in_line);
}

bool	parse(char *line) 
{
	t_token	*token_list;

	token_list = tokenization(line);
	//printf(RED "\nIn file: %s, line %d : " WHT, __FILE__, __LINE__ + 1);//-
	//explore_token_list(token_list->first);
	// print_all_token(token_list->first);//-
	free_list(token_list->first);
	return (0);
}

int32_t main(void)
{
	char	*rline;

	while (1)
	{
		rline = readline(RED "minishell> ");
		add_history(rline);
		parse(rline);
	}
	return (0);
}
