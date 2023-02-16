#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// #include "libft.h"
// #include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <limits.h>

#define NO_QUOTE 1
#define SGL_QUOTE 2
#define DBL_QUOTE 3
#define DOLLA_DBL_QUOTE 4


// ------------------------ Env Utils To Remove -------------------------------

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}   t_env;

size_t		ft_strlen(char *str)
{
	int		i;

	if (!*str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	no_quote_env_var_len_name(char *env_value)
{
	size_t	i;

	i = 1;
	while (env_value[i] && (env_value[i] != '$' && i != 0))
		i++;
	return (i);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	while ((*s1 || *s2) && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (0);
	return (1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;


	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	// Free
	// if (!str)
	// 	return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j])
		str[i++] = s2[j];
	str[i] = '\0';


	// POSSIBLE LEEK

	return (free(s1), str);
	// return (free(s1), free(s2), str);
}

t_env	*create_env_node(void)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->next = NULL;
	return (node);
}

void	create_linked_list(t_env **env_lst, char **envp)
{
	t_env		*node;
	int			i;

	i = 1;
	node = create_env_node();
	// if (!philo)
	// 	return (ERROR);
	*env_lst = node;
	i = 0;
	while (envp[i])
		i++;
	while (i)
	{
		node = *env_lst;
		while (node->next)
			node = node->next;
		node->next = create_env_node();
		// if (!env)
		// 	return (ERROR);
		i--;
	}
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	while (s[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (s[++i])
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}

char	*set_env_var_name(char *env_line)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	while (env_line[len] && env_line[len] != '=')
		len++;
	str = malloc(sizeof(char) * len + 1);
	// if(!node->name)
	// free
	i = 0;
	while (i < len)
	{
		str[i] = env_line[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

bool	env_cmd_value_check(char *env_line)
{
	int		i;

	i = 0;
	while (env_line[i])
	{
		if (env_line[i] == '=')
			return (false);
		i++;
	}
	return (true);
}

char	*set_env_node_value(char *env_line)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	// if (env_cmd_value_check(env_line) == false)
	// 	return (NULL);
	i = 0;
	while (env_line[i] != '=')
		i++;
	len = (ft_strlen(env_line) - (i + 1));
	str = malloc(sizeof(char) * len + 1);
	// free
	j = 0;
	while (j < len)
	{
		str[j] = env_line[i + 1];
		i++;
		j++;
	}
	str[len] = '\0';
	return (str);
}

void	set_env(t_env **env_lst, char **envp)
{
	t_env	*env_node;
	int		i;

	env_node = *env_lst;
	i = 0;
	while (envp[i])
	{
		env_node->name = set_env_var_name(envp[i]);
		env_node->value = set_env_node_value(envp[i]);
		env_node = env_node->next;
		i++;
	}
}

int		in_quote_len(char *r_line, char quote)
{
	int		len;

	len = 0;
	while ((r_line[len + 1] != quote) && (r_line[len] != '\\'))
		len++;
	return (len);
}

char	*remove_quote(char *arg, char quote)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	len = in_quote_len(arg, '\"');
	str = malloc(sizeof(char) * len + 1);
	// free
	i = 0;
	j = 1;
	while (i < len)
	{

		str[i] = arg[i + 1];
		i++;
	}
	str[i] = '\0';
	// free(arg);
	return (str);
}

char	*remove_quote_and_dollar(char *arg, char quote)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	// if (!arg)
	// 	return ;
	len = in_quote_len(arg + 1, '\"');
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * len + 1);
	// Free
	while (i < len)
	{
		str[i] = arg[i + 2];
		i++;
	}
	str[i] = '\0';
	// free(arg);
	return (str);
}

// ----------------------------------------------------------------------------

// -------------------------------- Expend ------------------------------------



char	*get_splitted_env_name(char *arg)
{
	char	*str;
	int		i;
	int 	len;

	len = 0;
	while (arg[len])
	{
		if (!arg[len] || arg[len] == '$'
			|| arg[len] == '\'' || arg[len] == '\"')
			break;
		len++;
	}
	str = malloc(sizeof(char) * len + 1);
	// Free
	i = 0;
	while (i < len)
	{
		str[i] = arg[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*expended_env_var(t_env **env_lst, char *arg)
{
	t_env	*env_node;
	char	*v_name;
	char	*value;

	env_node = *env_lst;
	if (arg[0] == '$')
	{
		v_name = get_splitted_env_name(arg + 1);
		while (env_node->next)
		{
			if (ft_strcmp(v_name, env_node->name))
			{
				value = ft_strdup(env_node->value);
				free(v_name);
				return (value);
			}
			env_node = env_node->next;
		}
	}
	free(v_name);
	value = malloc(sizeof(char) * 1);
	value[0] = '\0';
	return (value);
}



int		dollar_quote_len(char *r_line, char quote)
{
	int		len;

	len = 0;
	while ((r_line[len + 2] != quote) && (r_line[len + 1] != '\\'))
		len++;
	return (len);
}

// -------------------------- Dolla Sgl Quote ---------------------------------

char	*dollar_sgl_quote_pathern_str(char *r_line)
{
	char 	*str;
	int		len;
	// int		i;

	if (r_line[0] == '$' && r_line[1] == '\'')
	{
		len = dollar_quote_len(r_line, '\'');
		if (len == 0)
			return (NULL);
		str = malloc(sizeof(char) * len + 1);
		// Free
		str[len] = '\0';
		len--;
		while (len >= 0)
		{
			str[len] = r_line[len + 2];
			len--;			
		}
		return (str);
	}
	return (NULL);
}

// ----------------------------------------------------------------------------

// ---------------------------- Dolla Dbl Quote -------------------------------

char	*dollar_dbl_quote_pathern_str(char *r_line)
{
	char	*str;
	int		len;
	// int		i;

	if (r_line[0] == '$' && r_line[1] == '\"')
	{
		len = dollar_quote_len(r_line, '\"');
		if (len == 0)
			return (NULL);
		str = malloc(sizeof(char) * len + 2);
		// Free
		str[len + 1] = '\0';
		while (len >= 1)
		{
			str[len] = r_line[len + 1];
			len--;
		}
		str[0] = '$';
		return (str);
	}
	return (NULL);
}

bool	dollar_with_env_name(char *r_line, char quote, int i)
{
	if (r_line[i] == '$' && (r_line[i + 1] != ' ' && r_line[i + 1] != '\t' && 
		(r_line[i + 1] != quote && r_line[i - 1] != '\\') && r_line[i + 1] != '$'))
		return (true);
	return (false);
}

int		quoted_env_var_len_name(char *r_line, char quote)
{
	int	len;

	len = 0;
	while (r_line[len])
	{
		if (r_line[len] == ' ' || r_line[len] == '\t' || 
			(r_line[len] == quote && r_line[len - 1] != '\\') || r_line[len] == '$')
			break;
		len++;
	}
	return (len);
}

char	*look_for_env_value_name(char *r_line, int i ,int len)
{
	char	*value;

	value = malloc(sizeof(char) * len + 1);
	// Free
	len--;
	value[len + 1] = '\0';
	while (len >= 0)
	{
		value[len] = r_line[i + len];
		len--;
	}
	return (value);
}

char	*ft_front_str(char *r_line, int front_del)
{
	char	*front_str;
	int		i;

	if (front_del == 0)
	{
		front_str = malloc(sizeof(char) * 1);
		front_str[0] = '\0'; 
		return (front_str);
	}
	front_str = malloc(sizeof(char) * front_del + 1);
	// Free
	i = 0;
	while (i < front_del)
	{
		front_str[i] = r_line[i];
		i++;
	}
	front_str[i] = '\0';
	return (front_str);
}

char	*ft_back_str(char *r_line)
{
	char	*back_str;
	int		len;
	int		i;

	len = 0;
	while (r_line[len] && (r_line[len] != '\'' && r_line[len - 1] != '\\'))
		len++;
	back_str = malloc(sizeof(char) * len + 1);
	// Free
	i = 0;
	while (i < len)
	{
		back_str[i] = r_line[i];
		i++;
	}
	back_str[i] = '\0';
	return (back_str);
}

char	*expended_line(t_env **env_lst, char *r_line, int i, int len, char *val)
{
	char	*new_r_line;
	char	*front;
	char	*back;
	char	*first_half_r_line;

	front = ft_front_str(r_line, i);
	first_half_r_line = malloc(sizeof(char) * ft_strlen(r_line) - len
		+ ft_strlen(val));
	first_half_r_line = ft_strjoin(front, val);
	back = ft_back_str(&r_line[i + len + 1]);
	new_r_line = ft_strjoin(first_half_r_line, back);
	free(val);
	return (new_r_line);
}

char	*expend_in_double_quote(t_env **env_lst, char *r_line, int id)
{
	char	*new_r_line;
	char 	*expended_value;
	char	*value;
	int		len;
	int		i;

	new_r_line = NULL;
	i = 0;
	while (r_line[i])
	{
		if (dollar_with_env_name(r_line, '\"', i))
		{
			len = quoted_env_var_len_name(&r_line[i + 1], '\"');
			value = look_for_env_value_name(r_line, i, len + 1);
			expended_value = expended_env_var(env_lst, value);
			new_r_line = expended_line(env_lst, r_line, i, len, expended_value);
			i += ft_strlen(value);
			r_line = new_r_line;
		}
		else
			i++;
	}


	if (id == DOLLA_DBL_QUOTE)
	{

		if (new_r_line == NULL)
		{
			r_line = remove_quote_and_dollar(r_line, '\"');
			return (r_line);
		}
		new_r_line = remove_quote_and_dollar(new_r_line, '\"');
		return (new_r_line);
	} 

	if (new_r_line == NULL)
	{
		r_line = remove_quote(r_line, '\"');
		return (r_line);
	}
	new_r_line = remove_quote(new_r_line, '\"');
	return (new_r_line);


	// r_line = expended_dbl_quote_str(r_line, new_r_line);
	// return (new_r_line);

}

// ----------------------------------------------------------------------------

// ------------------------------ Sgl Quote -----------------------------------



char	*sgl_quote_pathern(char *arg)
{
	char	*str;
	int		len;
	int		i;

	len = in_quote_len(arg, '\'');
	// printf(">> %d\n", len);
	str = malloc(sizeof(char) * len + 1);
	// Free
	i = 0;
	while (i < len)
	{
		str[i] = arg[i + 1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// ----------------------------------------------------------------------------

// ------------------------------ No Quote ------------------------------------

int		no_quote_arg_len(char *arg)
{
	int		len;

	len = 0;
	while (arg[len] && (arg[len] != '$'
		&& (arg[len] != '\'' && arg[len - 1] != '\\')
		&& (arg[len] != '\"' && arg[len - 1] != '\\')))
		len++;
	return (len);
}

char	*no_quote_arg(char *arg, int len)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (len + 1));
	// Free
	i = 0;
	while (i < len)
	{
		str[i] = arg[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// ----------------------------------------------------------------------------

char *exp_str(char *arg, char *tmp)
{
	char *str;

	if (!arg)
		str = tmp;
	else
		str = ft_strjoin(arg, tmp);
	return (str);
}

int main(int ac, char **av, char **envp)
{
	t_env	*env_lst;
    char	*r_line;
	char	*arg;
	char 	*tmp;
	int		i;
	int		len;

	(void)ac;
	(void)av;

	create_linked_list(&env_lst, envp);
	set_env(&env_lst, envp);

	while (1)
	{
		i = 0;
		arg = NULL;
		r_line = readline("ghettoshell> ");
		while (r_line[i])
		{
			if (r_line[i] == '$' && r_line[i + 1] == '\'')
			{
				len = dollar_quote_len(&r_line[i], '\'') + 3;
				tmp = dollar_sgl_quote_pathern_str(&r_line[i]);
			}
			else if (r_line[i] == '$' && r_line[i + 1] == '\"')
			{
				len = dollar_quote_len(&r_line[i], '\"') + 3;
				tmp = expend_in_double_quote(&env_lst, &r_line[i], DOLLA_DBL_QUOTE);
			}
			else if (r_line[i] == '$')
			{
				len = no_quote_env_var_len_name(&r_line[i]);
				tmp = expended_env_var(&env_lst, &r_line[i]);
			}
			else if (r_line[i] == '\"')
			{
				len = in_quote_len(&r_line[i], '\"') + 2;
				tmp = expend_in_double_quote(&env_lst, &r_line[i], DBL_QUOTE);
			}
			else if (r_line[i] == '\'')
			{
				len = in_quote_len(&r_line[i], '\'') + 2;
				tmp = sgl_quote_pathern(&r_line[i]);
			}
			else
			{
				len = no_quote_arg_len(&r_line[i]);
				tmp = no_quote_arg(&r_line[i], len);
			}
			arg = exp_str(arg, tmp);
			i += len;
		}
		printf("--------------------------------------------------------------\n");
		printf("|  expend: '%s'\n", arg);
		printf("--------------------------------------------------------------\n");
		free(arg);
	}
}
