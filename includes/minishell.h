/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:18:54 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/07 03:11:33 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ========================================================================= //
//                                   Library                                 //
// ========================================================================= //

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <stdint.h>

// ========================================================================= //
//                                   Define                                  //
// ========================================================================= //

# define RED "\033[31m"
# define YLW "\033[33m"
# define WHT "\033[30m"

// ========================================================================= //
//                                    Enum                                   //
// ========================================================================= //

enum e_special {
	SPACE_BIS = 1,
	SINGLE_Q,
	DOUBLE_Q,
	HERE_DOC,
	IN_FILE,
	OUT_FILE,
	OUT_FILE_APPEND,
	PIPE,
	CMD,
	ARG,
	LIMITER,
};

enum e_token_type {
	START,
	CMD, // after start, after file, after pipe (if not recognized), after limiter
	PIPE,
	HERE_DOC,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	FILE, // after redir 
	LIMITER, // after here_doc
	WORD, //after command, after word, after here_doc
	END,
}

// ========================================================================= //
//                                 Structure                                 //
// ========================================================================= //

typedef struct s_token {
	int				type; // enum e_token_type
	char			*name; //content
	struct s_token	*first;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

// ========================================================================= //
//                                  Parsing                                  //
// ========================================================================= //
/**/
t_token	*pt_tokenization(char *line);

void	explore_token_list(t_token *token);
/*Check if characer is a space*/
bool	pt_is_space(int8_t character);

/*Check if charactere is special, if isn't return (0).*/
int16_t	pt_is_special(int8_t character);

/*Check if the character is one of quote. If it is, return an id to 
identify witch type of quote is it, to identify witch type of quote 
we need to close quoting. */
int16_t	pt_is_quote(int8_t charater);

/*Browse on the line, to find the good quote_type to close actual quoting.
If don't find the good quote to end,
copy start_quote until EOF.*/
char	*pt_get_quoting(int16_t quote_type, char *quote_start);

/*Malloc a string containing the full content of the quotes.
Add it in t_token->name and return the lenght of the quote*/
int32_t	pt_full_quote(int32_t offset_in_line, char *line, t_token *token_node);

/*Check if the character is a special char, or if a character is a white space
with a valid charactere behind*/
bool	pt_is_special_char(char *c);

/*Call all parsing fuctions*/
bool	pt_parse(char *line);


/*Is a ft_strdup with one more mallocated character, cause of the index of a
start to 0*/
char	*pt_extraction_from_line(int32_t n, char *original);

/*Init a node, skip first space in line, fill the token_list->name,
increment the offset, create a new line with the remainder, create new node
and continu until remainder is only EOF*/

/*Init first_node of the linked list*/
t_token	*pt_init_node(void);

/*Create a new_node to chain with the list*/
t_token	*pt_create_new_node(t_token *existing_node);

//------------------------------- pt_special.c -----------------------------.//
/*check if character is a space*/
bool	pt_is_space(int8_t character);

/*check if character is speical char*/
int16_t	pt_is_special(int8_t character);

/*extract the special from the line*/
char	*get_special(int32_t offsett_in_line, char *line, t_token *token_node);

/*increment until to be on the last character who's not a special*/
int16_t	pt_skip_until_special_is_next(char *line);

/*free node which only spaces characters*/
void	clean_spaces_nodes(t_token *token);


//-----------------------------p_tokenization.c -----------------------------.//
/*cut the readline into tokens*/
t_token	*pt_tokenization(char *line);

/*set up the line to get_token, and create a new line with only the part who's
not been treated*/
char	*pt_token_extracting(char *line, t_token *token);

/*First step: If the first char is a quote, get the type,
and try to catch the end of quote Else : The first char isn't a quote but  is 
special, so create a token for it. If noo speciaal, extract the part of line 
on a token*/
int32_t	pt_get_token(int32_t offset_in_line, char *line, t_token *token_node);

//-----------------------------ptt_typing_token.c --------------------------.//
void	ptt_typing_token(t_token *token_list);
// ========================================================================= //
//                                    Exec                                   //
// ========================================================================= //

// ========================================================================= //
//                                    Utils                                  //
// ========================================================================= //

char	*ft_strdup(const char *str);
char	*ft_strndup(char *buffer, size_t n);
size_t	ft_strlen(const char *s);
void	*pt_free_list(t_token *list);
void	free_node(t_token *node);

// ========================================================================= //
//                                    Test                                   //
// ========================================================================= //
void	print_all_token(t_token *token);
void	print_node(t_token *token);

#endif
