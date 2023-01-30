// #include "libft.h"
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
#include <minishell.h>

////



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




/////
//check if the character is one of quote. If it is, return an id to identify witch type of quote
//is it, to identify witch type of quote we need to close quoting.
int	is_quote(char charater)
{
	if (charater == '\'')
		return (-1);
	if (charater  == '"')
		return (-2);
	if (charater  == '`')
		return (-3);
	return (0);
	
}

bool	is_space(char character)
{
	if ((character >= 9 && character <= 13) || character == 32)
		return (1);
	return (0);
}

//Check if charactere is special, if isn't return (0).
int	is_special(char *line)
{
	if (*line == '<')
	{
		if (*line + 1 == '<')
			return (1);
		return (2);
	}
	if (*line == '>')
	{
		if (*line + 1 == '>')
			return (3);
		return (4);
	}
	if (*line == '|')
		return (5);
	if (*line == '\'' || *line == '"' || *line == '`')
		return (34);
	return (0);
}



//Browse on the line, to find the good quote_type to close actual quoting. If don't find the good quote to end,
//copy start_quote until EOF.
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

int	pt_is_special_char(char *c)
{
	if (is_space(*c) && !is_space(*(c + 1)))
		return (1);
	if (is_quote(*c))
		return (1);
	if (is_special(c))
		return (1);
	return (0);
}

//First step: If the first char is a quote, get the type, and try to catch the end of quote
//Else : The first char isn't a quote;
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
		if (!token_node->name)
		{
			ERR
			exit(EXIT_FAILURE);
		}
		return (offset_in_line + ft_strlen(token_node->name));
	}
	token_node->name = extracted_from(offset_in_line, line);
	if (!token_node->name)
	{
		ERR
		exit(EXIT_FAILURE);
	}
	return (offset_in_line);
}
/////

//init a node, skip first space in line, fill the token_list->name, increment the offset, create a new line with the remainder,
//create new node and continu until remainder is only EOF
t_token *token_recognition(char *line)
{
	int			offset_in_line;
	char		*remainder;
	t_token		*token_list;

	offset_in_line = 0;
	token_list = init_node();
	printf("1\n");
	while (line[offset_in_line])
	{
		while(line[offset_in_line] && is_space(line[offset_in_line]) && offset_in_line++)
			;
		printf("3\n");
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
		printf("offset :%s\n", remainder);
		print_node(token_list);//-
		printf(RED "After extract %s from line, remainder is: %s\n" WHT, token_list->name, line);//-
		offset_in_line = 0;
		token_list->next = create_new_node(token_list);
		token_list = token_list->next;
		printf("6\n");
	}
	return (token_list->first);
}
////



int	parse(char *line)
{
	t_token	*token_list;

	token_list = token_recognition(line);
	printf(RED "\nIn file: %s, line %d : " WHT, __FILE__, __LINE__ + 1);//-
	//print_all_token(token_list->first);//-
}

int main(void)
{
	char	*rline;

	while (1)
	{
		rline = readline("minishell> ");
		add_history(rline);
		parse(rline);
	}
	return (0);
}
