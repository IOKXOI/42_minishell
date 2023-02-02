/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 05:01:04 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/02 08:18:53 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

short	is_quote(char charater)
{
	if (charater == '\'')
		return (QUOTE);
	if (charater  == '"')
		return (QUOTES);
	if (charater  == '`')
		return (QUOTES_BIS);
	return (0);
	
}

char	*get_quoting(int quote_type, char *quote_start)
{
	int		offset_in_quote;
	char	*token;

	offset_in_quote = 1;
	while (quote_start[offset_in_quote] && ((is_quote(quote_start[offset_in_quote]) != quote_type)))
		offset_in_quote++;
	token = extraction_from_line(offset_in_quote + 1, quote_start);
	return (token);
}

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

// char	*get_special(int type, char *special_in_line)
// {
// 	char	*start;
// 	(void)type;

// 	start = special_in_line;
// 	while (*special_in_line && (is_special(special_in_line) || is_space(special_in_line)))
// 		special_in_line++;
// 	return (ft_strndup(start, special_in_line - start));
// }

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

// int	get_token(char *line, t_token *token_node)
// {
// 	int		offset_in_line;
// 	int		quote_type;

// 	offset_in_line = 0;
// 	token_node->token = is_special(line + offset_in_line);
// 	if (token_node->token == QUOTES)
// 	{
// 		quote_type = is_quote(line[offset_in_line]);
// 		token_node->name = get_quoting(quote_type, line + offset_in_line);
// 		offset_in_line += ft_strlen(token_node->name);
// 	}
// 	else if (token_node->token >= HERE_DOC && token_node->token <= PIPE)
// 	{
// 		token_node->name = get_special(token_node->token, line + offset_in_line);
// 		offset_in_line += ft_strlen(token_node->name);
// 	}
// 	else
// 		token_node->name = extraction_from_line(offset_in_line, line);
// 	if (!token_node->name || offset_in_line < 0)
// 	{
// 		ERR
// 		exit(EXIT_FAILURE);
// 	}
// 	return (offset_in_line);
// }

int32_t	skip_until_special(char *line)
{
	int32_t	offset_in_line;

	offset_in_line = 0;
	if (is_special(line [offset_in_line]))
		return (offset_in_line);
	while (line[offset_in_line] && !is_special(line[offset_in_line + 1]))
		offset_in_line++;
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
		offset_in_line += skip_until_special(line + offset_in_line);
		if (!line[offset_in_line] && !offset_in_line)
			return (NULL);
		token_list->name = extraction_from_line(offset_in_line, line);
		if (!token_list->name)
		{
			free_list(token_list->first);
			free(line);
			exit (1);
		}
		remainder = ft_strdup(line + offset_in_line + 1);
		if (!remainder && line[offset_in_line])
		{
			free_list(token_list->first);
			free(line);
			exit (1);
		}
		free(line);
		line = remainder;
		print_node(token_list);//-
		printf(RED "After extraction ." YLW"%s" RED ".from line, remainder is: ." YLW"%s" RED".\n"WHT, token_list->name, line);//-
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
