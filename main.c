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
	new_line = malloc(sizeof(char) * n + 1);
	if (!new_line)
		return (NULL);
	while (i < n)
	{
		new_line[i] = original[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}



void	*ft_memmove(void *dest, const void *src, size_t size)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (src > dest && size--)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	while (dest > src && size--)
		*(unsigned char *)(dest + size) = *(unsigned char *)(src + size);
	return (dest);
}



/////
//check if the character is one of quote. If it is, return an id to identify witch type of quote
//is it, to identify witch type of quote we need to close quoting.
int	is_quote(char charater)
{
	if (charater == '\'')
		return (1);
	if (charater  == '"')
		return (2);
	if (charater  == '`')
		return (3);
	return (0);
	
}

//Check if charactere is special, if isn't return (0).
int	is_special(char *line)
{
	if (*line == '<')
	{
		if (++(*line) == '<')
			return (4);
		return (5);
	}
	if (*line == '>')
	{
		if (++(*line) == '>')
			return (6);
		return (7);
	}
	if (*line == '|')
		return (8);
	return (is_quote(*line));
}

int	is_white_space(char line)
{
	if ((line >= 9 && line <= 13) || line == 32)
		return (1);
	return (0);
}




//check if the quote is preceded of a backslash or not.
int	prev_is_backslash(int i, char *quote)
{
	if (!is_quote(quote[i]))
		return (0);
	if (i > 1 && quote[i - 1] == '\\')
		return (1);
	return (0);
}

//Browse on the line, to find the good quote_type to close actual quoting. If don't find the good quote to end,
//copy start_quote until EOF.
char	*get_quoting(int quote_type, char *quote_start)
{
	int		i;
	char	*token;

	i = 0;
	while (quote_start[i] && ((is_quote(quote_start[i]) != quote_type) && !prev_is_backslash(i, quote_start)))
		i++;
	token = extracted_from(i, quote_start);
	return (token);
}


//First step: If the first char is a quote, get the type, and try to catch the end of quote
//Else : The first char isn't a quote;
void	get_token(char *line, t_token *token_node)
{
	int	i;
	int	quote_type;
	int	special_char;

	i = 0;
	// if (is_quote(line[0]))
	// {
	// 	token_node->name = get_quoting(quote_type, &line[0]);
	// 	if (!token_node->name)
	// 	{
	// 		ERR
	// 		//free_linked_list();
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	return (ft_strlen(token_node->name));
	//}
	while(line[i] && !is_special(&line[i]) && !is_white_space(line[i]))
		i++;
	quote_type = is_quote(line[i]);
	special_char = is_special(&line[i]);
	if (quote_type)
	{
		token_node->name = get_quoting(quote_type, &line[i]);
		if (!token_node->name)
		{
			ERR
			exit(EXIT_FAILURE);
		}
		return;
	}
	else if (special_char)
	{
		if (i == 0)
			i++;
		else
			i--;
	}
	token_node->name = extracted_from(i, line);
	if (!token_node->name)
	{
		ERR
		exit(EXIT_FAILURE);
	}
	if (!ft_memmove(&line[0], &line[i], ft_strlen(&line[i]))
		free(line);
	printf(RED "After extract %s from line, remainder is: %s\n" WHT, token_node->name, line);//-
	return;
}
/////

t_token *token_recognition(char *line)
{
	int	i;
	t_token	*token_list;

	i = 0;
	token_list = init_node();
	print_node(token_list);
	get_token(line, token_list);
	printf(RED "\nIn file: %s, line %d : " WHT, __FILE__, __LINE__ + 1);//-
	print_node(token_list);//-
	while (line[i])
	{
		token_list->next = create_new_node(token_list);
		token_list = token_list->next;
		get_token(line, token_list);
		printf("\n NEW_NODE :");	
		print_node(token_list);
	}
}
////



int	parse(char *line)
{
	t_token	*token_list;

	token_list = token_recognition(line);
	printf(RED "\nIn file: %s, line %d : " WHT, __FILE__, __LINE__ + 1);//-
	print_all_token(token_list->first);//-
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
