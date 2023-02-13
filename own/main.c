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

// ------------------------------ Header File ---------------------------------

#define NO_OUT_FILE -404

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}   t_env;

// typedef struct s_cmd
// {
// 	int			in_file;
// 	int			out_file;
// 	struct s_env	*next;
// }   t_cmd;

// ----------------------------------------------------------------------------

// ------------------------------ Utils ---------------------------------------

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

// Also located in echo.c file
int		ft_arg_count(char **av)
{
	int		i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

// ----------------------------------------------------------------------------

// --------------------- Set Env Linked List ----------------------------------

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

// --------------------------- Env Built In -----------------------------------
void	exec_env_built_in(t_env **env_lst, int fd/*, t_cmd *cmd_node*/)
{
	t_env	*env_node;		

	// TODO: -Check error else return
	env_node = *env_lst;
	fd = 0;
	while (env_node->next)
	{
		write(fd, env_node->name, ft_strlen(env_node->name));
		write(fd, "=", 1);
		write(fd, env_node->value, ft_strlen(env_node->value));
		write(fd, "\n", 1);
		env_node = env_node->next;
	}
}

// ----------------------------------------------------------------------------

// ------------------------- Export Built In ----------------------------------

bool	underscore_value_name(char *env_var_name)
{
	if (ft_strcmp(env_var_name, "_"))
		return (true);
	return (false);
} 

bool	replace_env_value(t_env **env_lst, char *arg)
{
	t_env	*env_node;
	char	*str;
	
	env_node = *env_lst;
	str = set_env_var_name(arg);
	if (underscore_value_name(str))
	{
		free (str);
		return (true);
	}
	while (env_node->next)
	{
		if (ft_strcmp(env_node->name, str))
		{
			free(env_node->value);
			env_node->value = set_env_node_value(arg);
			return (true);
		}
		env_node = env_node->next;
	}
	free(str);
	return (false);
}

void	add_new_env_var(t_env **env_lst, char *arg)
{
	t_env	*env_node;
	t_env	*tmp;

	env_node = *env_lst;
	while (env_node->next->name != NULL)
		env_node = env_node->next;
	tmp = env_node->next;
	env_node->next = create_env_node();
	env_node = env_node->next;
	env_node->name = set_env_var_name(arg);
	env_node->value = set_env_node_value(arg);
	env_node->next = tmp;
}

int		alpha_arg_count(t_env **env_lst, int letter)
{
	t_env	*env_node;
	int		count;

	env_node = *env_lst;
	count = 0;
	while (env_node->next->name != NULL)
	{
		if (env_node->name[0] == letter)
			count++;
		env_node = env_node->next;
	}
	return (count);
}

t_env	**create_alpha_env_arr(t_env **env_lst, int arg_count, int letter)
{
	t_env	**arg_arr;
	t_env	*env_node;
	int		i;

	arg_arr = malloc(sizeof(t_env *) * arg_count);
	// Free
	env_node = *env_lst;
	i = 0;

	while (env_node->next)
	{
		if (env_node->name[0] == letter)
		{
			arg_arr[i] = create_env_node();
			arg_arr[i]->name = env_node->name;
			arg_arr[i]->value = env_node->value;
			i++;
		}
		env_node = env_node->next;
	}
	return (arg_arr);
}

t_env	**sort_env(t_env **env_arr, int count)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count)
		{
			if (ft_strcmp(env_arr[i]->name, env_arr[j]->name) > 0)
			{
				tmp = env_arr[i];
				env_arr[i] = env_arr[j];
				env_arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env_arr);
}

void	print_alpha_sort_env(t_env **env_lst, int arg_count, int fd)
{
	int		i;

	i = 0;
	while (i < arg_count)
	{
		write(fd, env_lst[i]->name, ft_strlen(env_lst[i]->name));
		write(fd, "=", 1);
		write(fd, env_lst[i]->value, ft_strlen(env_lst[i]->value));
		write(fd, "\n", 1);
		i++;
	}
}

void	free_alpha_sort_env_arr(t_env **env_arr, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		free(env_arr[i]);
		i++;
	}
	free(env_arr);
}

void	export_without_args_exec(t_env **env_lst, int fd)
{
	t_env			**arg_arr;
	unsigned int 	letter;
	int				word_count;
	
	letter = 32;
	while (letter <= 255)
	{
		word_count = alpha_arg_count(env_lst, letter);
		if (word_count > 0)
		{
			arg_arr = create_alpha_env_arr(env_lst, word_count, letter);
			arg_arr = sort_env(arg_arr, word_count);
			print_alpha_sort_env(arg_arr, word_count, fd);
			free_alpha_sort_env_arr(arg_arr, word_count);
		}
		letter++;
	}
}

void	exec_export_built_in(t_env **env_lst, int ac, char *arg, int fd)
{
	if (ac < 2 || ac > 3)
		return ;
	if (ac == 2)
	{
		export_without_args_exec(env_lst, fd);
		return ;
	}
	if (replace_env_value(env_lst, arg))
		return ;
	else
		add_new_env_var(env_lst, arg);
}

// ----------------------------------------------------------------------------

// -------------------------- Unset Built In ----------------------------------

void	free_env_node(t_env *env_node)
{
	free(env_node->name);
	free(env_node->value);
	free(env_node);
}

void	exec_unset_built_in(t_env **env_lst, char *arg)
{
	t_env	*env_node;
	t_env	*tmp;

	env_node = *env_lst;
	if (ft_strcmp(env_node->name, arg))
	{
		tmp = *env_lst;
		*env_lst = (*env_lst)->next;
		free_env_node(tmp);
		return ;
	}
	while (env_node->next->name != NULL)
	{
		if (ft_strcmp(env_node->next->name, arg))
		{
			tmp = env_node->next;
			env_node->next = tmp->next;
			free_env_node(tmp);
			return ;
		}
		env_node = env_node->next;
	}
}

// ----------------------------------------------------------------------------

// ------------------------------- Cd Command ---------------------------------

bool	cd_cmd_line_check(int arg_count)
{
	if (arg_count > 3) // Set to 2
	{
		write(2, "bash: cd: too many arguments\n", 29);
		return (false);
	}
	return (true);
}

t_env	*get_pwd_node(t_env **env_lst)
{
	t_env	*env_node;

	env_node = *env_lst;
	while (env_node->next)
	{
		if (ft_strcmp(env_node->name, "PWD"))
			return (env_node);
		env_node = env_node->next;
	}
	return (NULL);
}

t_env	*get_old_pwd_node(t_env **env_lst)
{
	t_env	*env_node;

	env_node = *env_lst;
	while (env_node->next)
	{
		if (ft_strcmp(env_node->name, "OLDPWD"))
			return (env_node);
		env_node = env_node->next;
	}
	return (NULL);
}

void	set_old_pwd(t_env **env_lst, t_env *old_pwd_node, char *path)
{
	t_env	*env_node;
	t_env	*tmp;

	env_node = *env_lst;
	if (old_pwd_node == NULL)
	{
		while (env_node->next->name)
			env_node = env_node->next;
		tmp = create_env_node();
		tmp->name = set_env_var_name("OLD_PWD");
		tmp->value = set_env_var_name(path);
		tmp->next = env_node->next;
		env_node->next = tmp;
		return ;
	}
	free(old_pwd_node->value);
	old_pwd_node->value = path;
}

void	set_pwd(t_env **env_lst, t_env *pwd_node)
{
	t_env	*env_node;
	char	*path;

	env_node = *env_lst;
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	if (pwd_node == NULL)
	{

		env_node = create_env_node();
		env_node->name = set_env_var_name("PWD");
		env_node->value = set_env_var_name(path);
		env_node->next = *env_lst;
		*env_lst = env_node;
		return ; 
	}
	free(pwd_node->value);
	pwd_node->value = set_env_var_name(path);
}

// void	set_old_pwd_var(t_env *pwd_node, t_env *old_pwd_node, char *prev_path)
// {
// 	int		loop_count;

// 	if (old_pwd_node == NULL)
// 	{

// 	}
// 		return ;
// 	loop_count = 0;
// 	if (loop_count == 0)
// 	{
// 		loop_count = 1;
// 		return ;
// 	}
// 	free(old_pwd_node->value);
// 	old_pwd_node->value = pwd_node->value;
	
// }

bool	chdir_error_check(int path_id, char *arg)
{
	if (path_id != -1)
		return (false);
	write(2, "bash: cd: ", 10);
	write(2, arg, ft_strlen(arg));
	write(2, ": No such file or directory\n", 28);
	return (true);
}

bool	cd_without_args_exec(t_env **env_lst, char **arg)
{
	t_env	*env_node;
	char	*path;
	int		path_id;
	
	if (ft_arg_count(arg) > 2)
		return (false);
	env_node = *env_lst;
	while (env_node->next)
	{
		if (ft_strcmp(env_node->name, "HOME"))
		{
			path_id = chdir(env_node->value);
			// printf("%s\n", env_node->value);
			if (path_id == 0)
			    path = getcwd(NULL, 0);
			else
			{
				write(2, "cd: no such file or directory: ", 31);
				write(2, env_node->value, ft_strlen(env_node->value));
				write(2, "\n", 1);
			}
			return (true);
		}
		env_node = env_node->next;
	}
	return (false);
}

void	exec_cd_built_in(t_env **env_lst, char **arg)
{
	t_env	*pwd_node;
	t_env	*old_pwd_node;
	char	*prev_path;
	int		path_id;
	int		arg_count;

	if (cd_without_args_exec(env_lst, arg) == true)
		return ;
	arg_count = ft_arg_count(arg);	
	if (cd_cmd_line_check(arg_count) == false)
		return ;
	prev_path = getcwd(NULL, 0);
	path_id = chdir(arg[2]);
	if (chdir_error_check(path_id, arg[3]))
		return ;
	pwd_node = get_pwd_node(env_lst);
	old_pwd_node = get_old_pwd_node(env_lst);
	set_old_pwd(env_lst, old_pwd_node, prev_path);
	set_pwd(env_lst, pwd_node);
}

// ----------------------------------------------------------------------------

// ------------------------------- Pwd Built In -------------------------------

void	exec_pwd_built_in(int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
}

// ----------------------------------------------------------------------------

// ----------------------------- Expend ---------------------------------------

char	*expended_env_var(t_env **env_lst, char *arg)
{
	t_env	*env_node;

	env_node = *env_lst;
	if (arg[0] == '$')
	{
		while (env_node->next)
		{
			if (ft_strcmp(arg + 1, env_node->name))
				return (env_node->value);
			env_node = env_node->next;
		}
	}
	return (NULL);
}


//  || (arg[i] == '"' && arg[i + 1] == '$'))		len = (ft_strlen(arg) - i);

int main(int ac, char **av, char **envp)
{
		t_env	*env_lst;
	
	// int run_time = 0;


	// to set
	int fd = 1;

	// if (ac < 2)
	// {
	// 	printf("not enough arg\n");
	// 	return (1);
	// }
	create_linked_list(&env_lst, envp);
	set_env(&env_lst, envp);

// ----------------------------------------------------------------------------

	// CMD LINE
	if (ft_strcmp(av[1], "env"))
		exec_env_built_in(&env_lst, fd);
	if (ft_strcmp(av[1], "export"))
		exec_export_built_in(&env_lst, ac, av[2], fd);
	if (ft_strcmp(av[1], "unset"))
		exec_unset_built_in(&env_lst, av[2]);
	if (ft_strcmp(av[1], "cd"))
		exec_cd_built_in(&env_lst, av);
	if (ft_strcmp(av[1], "pwd"))
		exec_pwd_built_in(fd);

// ----------------------------------------------------------------------------

	// run_time++;

// // 	Print Env
// 	t_env *node;
// 	node = env_lst;
// 	while (node->next)
// 	{
// 		printf("%s=%s\n", node->name, node->value);
// 		node = node->next;
// 	}
}

// TODO: - Set a boolean tht indicate if the unset cmd: unset old_pwd has been done at least 1 time
