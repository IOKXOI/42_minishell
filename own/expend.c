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
	return (free(s1), free(s2), str);
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

// ----------------------------------------------------------------------------

// -------------------------------- Expend ------------------------------------



// char	*r_line_env_var(char	*arg, int state)
// {

// }

char	*expended_env_var(t_env **env_lst, char *arg)
{
	t_env	*env_node;
	// char	*v_name;
	char	*value;
	// int		len;

	env_node = *env_lst;
	if (arg[0] == '$')
	{
		// len = 1;
		// while (arg[len] != ' ' || arg[len] != '$' || arg[len] != '\0')
		while (env_node->next)
		{
			// v_name = r_line_env_var(arg, NO_QUOTE);
			
			if (ft_strcmp(arg + 1, env_node->name))
			{
				value = ft_strdup(env_node->value);
				return (value);
			}
			env_node = env_node->next;
		}
	}
	value = malloc(sizeof(char) * 1);
	value[0] = '\0';
	return (value);
}

int		in_quote_len(char c, char *r_line)
{
	int		len;

	len = 0;
	while ((r_line[len + 2] != c) && (r_line[len + 1] != '\\'))
		len++;
	return (len);
}


char	*dollar_sgl_quote_pathern_str(char *r_line)
{
	char 	*str;
	int		len;
	// int		i;

	if (r_line[0] == '$' && r_line[1] == '\'')
	{
		len = in_quote_len('\'', r_line);
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


char	*dollar_dbl_quote_pathern_str(char *r_line)
{
	char	*str;
	int		len;
	// int		i;

	if (r_line[0] == '$' && r_line[1] == '\"')
	{
		len = in_quote_len('\"', r_line);
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

int		env_var_name_len(char *r_line, char quote)
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

// char	*set_new_r_line()
// {
// 	char	*front;
// 	char	*back;



// }







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
	return (new_r_line);
}

char	*expend_in_double_quote(t_env **env_lst, char *r_line)
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
			len = env_var_name_len(&r_line[i + 1], '\"');
			value = look_for_env_value_name(r_line, i, len + 1);
			expended_value = expended_env_var(env_lst, value);
			new_r_line = expended_line(env_lst, r_line, i, len, expended_value);
			i += ft_strlen(value);
			r_line = new_r_line;
		}
		else
			i++;
	}
	if (new_r_line == NULL)
		return (r_line);
	return (new_r_line);
}

// ----------------------------------------------------------------------------

void	expend(t_env **env_lst, char *r_line)
{
	char	*arg;
	int		state;
	int		len;
	int		i;

	i = 0;
	while (r_line[i])
	{

		if (r_line[0] == '$' && r_line[i + 1] == '\'')
			arg = dollar_sgl_quote_pathern_str(&r_line[i]);
		else if (r_line[i] == '$' && r_line[i + 1] == '\"')
			arg = dollar_dbl_quote_pathern_str(&r_line[i]);
		else if (arg[i] == '$')
			arg = expended_env_var(env_lst, &r_line[i]);
		i++;
	}
}




int main(int ac, char **av, char **envp)
{
	t_env	*env_lst;
    char	*r_line;
	char	*str;

	(void)ac;
	(void)av;


	create_linked_list(&env_lst, envp);
	set_env(&env_lst, envp);
	while (1)
	{
		r_line = readline("minishell> ");

		// printf("%s\n\n", r_line_env_var(r_line, NO_QUOTE));


		// str = expended_env_var(&env_lst, r_line);
		// str = dollar_sgl_quote_pathern_str(r_line);
		str = expend_in_double_quote(&env_lst, r_line);
		// str = dollar_dbl_quote_pathern_str(r_line);

		printf("%s\n", str);
	}
}