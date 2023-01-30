#include "minishell.h"

void	print_node(t_token *token)
{
	printf(YLW"token:\nname = %s\n\
	type = %d\n\
	prev = %p\n\
	next = %p\n", token->name, token->token, token->prev, token->next);
	if (token->next)
	{
		printf("next token = %s\n", token->next->name);
	}
	printf("\n"WHT);
}

void	print_all_token(t_token *token)
{
	while (token)
	{
		print_node(token);
		token = token->next;
	}
}
