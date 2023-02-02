/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 05:01:04 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/02 11:12:49 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_space(char character)
{
	if ((character >= 9 && character <= 13) || character == 32)
		return (1);
	return (0);
}

short	is_special(char character)
{
	if (is_space(character))
		return(SPACE_BIS);
	if (character == '<')
		return (IN_FILE);
	if (character == '>')
		return (OUT_FILE);
	if (character == '|')
		return (PIPE);
	if (character == '\'' || character == '"' || character == '`')
		return (QUOTES);
	return (0);
}

char	*get_special(int offsett_in_line, char *line, t_token *token_node)
{
	while (is_special(line[offsett_in_line]))
		offsett_in_line++;
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

char	*extraction_from_line(int n, char *original)
{
	int		i;
	char	*new_line;

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

int32_t	skip_until_special_is_next(char *line)
{
	int32_t	offset_in_line;

	offset_in_line = 0;
	if (is_special(line [offset_in_line]))
		return (offset_in_line);
	while (line[offset_in_line] && !is_special(line[offset_in_line + 1]))
		offset_in_line++;
	return (offset_in_line);
}

int	get_token(int offset_in_line, char *line, t_token *token_node)
{
	token_node->type = is_special(line[offset_in_line]);
	if (token_node->type == QUOTES)
		return (full_quote(offset_in_line, line, token_node));
	else if (token_node->type)
		return (ft_strlen(get_special(offset_in_line, line, token_node)) - 1);
	else
		token_node->name = extraction_from_line(offset_in_line, line);
	if (!token_node->name || offset_in_line < 0)
	{
		ERR
		exit(EXIT_FAILURE);
	}
	return (0);
}

char	*token_extracting(char *line, t_token *token)
{
	int			offset_in_line;
	char		*remainder;
	
	offset_in_line = skip_until_special_is_next(line);
	offset_in_line += get_token(offset_in_line ,line, token);
	remainder = ft_strdup(line + offset_in_line + 1);
	free(line);
	return (remainder);
}

t_token *tokenization(char *line)
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

int	parse(char *line) 
{
	t_token	*token_list;

	token_list = tokenization(line);
	printf(RED "\nIn file: %s, line %d : " WHT, __FILE__, __LINE__ + 1);//-
	//print_all_token(token_list->first);//-
	return (0);
}

int main(void)
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
