/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 05:01:04 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/31 14:49:04 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

short	is_quote(char charater)
{
	if (charater == '\'')
		return (35);
	if (charater  == '"')
		return (36);
	if (charater  == '`')
		return (37);
	return (0);
	
}

char	*get_quoting(int quote_type, char *quote_start)
{
	int		offset_in_quote;
	char	*token;

	offset_in_quote = 1;
	while (quote_start[offset_in_quote] && ((is_quote(quote_start[offset_in_quote]) != quote_type)))
		offset_in_quote++;
	token = extracted_from(offset_in_quote + 1, quote_start);
	return (token);
}

bool	is_space(char character)
{
	if ((character >= 9 && character <= 13) || character == 32)
		return (1);
	return (0);
}

short	is_special(char *line)
{
	printf(YLW "\nok\n");
	if (*line == '<')
	{
		if (*line + 1 == '<')
			return (1);
		return (2);
	}
	if (*line == '>')
	{
		if (*line + 1 == '>')
			return (4);
		return (3);
	}
	if (*line == '|')
		return (5);
	if (*line == '\'' || *line == '"' || *line == '`')
		return (34);
	return (0);
}

char	*get_special(int type, char *special_in_line)
{
	int limit;
	
	limit = ft_strlen(special_in_line);
	if (limit < 2)
		return (NULL);
	if (type == IN_FILE || type == OUT_FILE || type == PIPE)
	{
		if (is_special(special_in_line + 1) || special_in_line[1] == EOF)
			return (NULL);
		return (ft_strndup(special_in_line, 1));
	}
	else if (type == HERE_DOC || type == OUT_FILE_APPEND)
	{
		if (is_special(special_in_line + 1) || *(special_in_line + 2) == EOF)
			return (NULL);
		return (ft_strndup(special_in_line, 2));
	}
	return (NULL);
}

bool	pt_is_special_char(char *c)
{
	if (is_space(*c) && !is_space(*(c + 1)))
		return (1);
	if (is_quote(*c))
		return (1);
	if (is_special(c))
		return (1);
	return (0);
}

char	*extracted_from(int n, char *original)
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

int	get_token(char *line, t_token *token_node)
{
	int		offset_in_line;
	int		quote_type;

	offset_in_line = 0;
	while (line[offset_in_line] && !pt_is_special_char(line + offset_in_line))
		offset_in_line++;
	token_node->token = is_special(line + offset_in_line);
	if (token_node->token == '"')
	{
		quote_type = is_quote(line[offset_in_line]);
		token_node->name = get_quoting(quote_type, line + offset_in_line);
		offset_in_line += ft_strlen(token_node->name);
	}
	else if (token_node->token >= HERE_DOC && token_node->token <= PIPE)
	{
		token_node->name = get_special(token_node->token, line + offset_in_line);
		offset_in_line += ft_strlen(token_node->name);
	}
	else
		token_node->name = extracted_from(offset_in_line, line);
	if (!token_node->name || offset_in_line < 0)
	{
		ERR
		exit(EXIT_FAILURE);
	}
	return (offset_in_line);
}

t_token *token_recognition(char *line)
{
	int			offset_in_line;
	char		*remainder;
	t_token		*token_list;

	offset_in_line = 0;
	token_list = init_node();
	while (line[offset_in_line])
	{
		while(line[offset_in_line] && is_space(line[offset_in_line]))
			offset_in_line++;
		offset_in_line += get_token(line, token_list);
		remainder = ft_strdup(line + offset_in_line);
		if (!remainder && line[offset_in_line])
		{
			free_list(token_list->first);
			free(line);
			exit (1);
		}
		free(line);
		line = remainder;
		print_node(token_list);//-
		printf(RED "After extract %s from line, remainder is: %s\n" WHT, token_list->name, line);//-
		offset_in_line = 0;
		token_list->next = create_new_node(token_list);
		token_list = token_list->next;
	}
	return (token_list->first);
}

int	parse(char *line)
{
	t_token	*token_list;

	token_list = token_recognition(line);
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
