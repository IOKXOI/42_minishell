/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:18:54 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/15 05:00:36 by sydauria         ###   ########.fr       */
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

enum e_type {
	WORD,
	START,
	SPACE_BIS,
	SINGLE_Q,
	DOUBLE_Q,
	CMD, // after start, after file, after pipe (if not recognized), after limiter
	HERE_DOC,
	LIMITER, // after here_doc
	REDIR_IN,
	IN_FILE,
	REDIR_OUT,
	REDIR_APPEND,
	OUT_FILE_APPEND,
	OUT_FILE,
	FILES, // after redir 
	PIPE,
//	WORD, //after command, after word, after here_doc
	END,
};

// ========================================================================= //
//                                 Structure                                 //
// ========================================================================= //

typedef struct s_token {
	enum e_type		type;
	char			*name;//content
	struct s_token	*first;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

typedef struct s_complete_cmd {
	char					*commande;
	char					*infile;
	char					*outfile;
	char					*outfile_append;
	char					*limiter;
	char					**args;
	struct s_complete_cmd	*first;
	struct s_complete_cmd	*prev;
	struct s_complete_cmd	*next;
}t_complete_cmd;

// ========================================================================= //
//                                  Parsing                                  //
// ========================================================================= //
/**/
t_token	*pt_tokenization(char *line);

void	explore_token_list(t_token *token);
/*Check if characer is a space*/
bool	pt_is_space(int8_t character);

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

//------------------------------- pt_special.c -----------------------------.//
/*check if character is a space*/
bool	pt_is_space(int8_t character);

/*check if character is speical char*/
enum	e_type	pt_is_special(int8_t character);

/*extract the special from the line*/
char	*get_special(int32_t offsett_in_line, char *line, t_token *token_node);

/*increment until to be on the last character who's not a special*/
int16_t	pt_skip_until_special_is_next(char *line);

/*free node which only spaces characters*/
void	clean_spaces_nodes(t_token *token);
/*____________________________________________________________________________*/


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


//------------------------------- pa_aggregation.c --------------------------.//
t_complete_cmd	*pa_aggregation(t_token *token_list);

//-----------------------------ptt_typing_token.c --------------------------.//
void	ptt_typing_token(t_token *token_list);

//--------------------------------pl_lexer.c -------------------------------.//
/*Calls functions who's check the next node to track syntax errors*/
bool	p_lexeur(t_token *token_list);

//--------------------------------pl_lexer.c -------------------------------.//
t_complete_cmd	*pta_aggregation(t_token *token_list);


//------------------------------- t_linked_list.c --------------------------.//
/*Init first_node of the linked list*/
t_token	*pt_init_node(void);

/*Create a new_node to chain with the list*/
t_token	*pt_create_new_node(t_token *existing_node);

/*Init first_node of the complete_cmd_list and set values to NULL*/
t_complete_cmd	*init_command_list(void);

/*Create new complete_cmd node, set values to NULL and link with last one*/
t_complete_cmd	*new_complete_cmd(t_complete_cmd *cmd_list);

// ========================================================================= //
//                                    Exec                                   //
// ========================================================================= //

// ========================================================================= //
//                                    Utils                                  //
// ========================================================================= //

void	*pt_free_list(t_token *list);
void	free_node(t_token *node);
char	*ft_strdup(const char *str);
char	*ft_strndup(char *buffer, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

// ========================================================================= //
//                                    Test                                   //
// ========================================================================= //
void	print_all_token(t_token *token);
void	print_node(t_token *token);

#endif
