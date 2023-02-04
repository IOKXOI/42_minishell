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

#define OUT_FILE 1

size_t		ft_strlen(char *str)
{
	int		i;

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




bool	echo_without_arg_behavior(char **av, int arg_count, int fd)
{
	if (arg_count == 2) // 1 not 2
	{
		write(fd, "\n", 1);
		return (true);
	}
	if (ft_strcmp(av[2], "-n") && arg_count == 3) // 1 not 2 + 2 not 3 
		return (true);
	return (false);
}

int		ft_arg_count(char **av)
{
	int		i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

void    exec_echo_built_in(char **av, int fd)
{
	// fd just above describing the outfile, will be 1 if no redir else it correspond to the outfile integer value

	int     i;
	int     arg_count;
	int     n_option;
	int     len;
	// value to determine inside the structure

	arg_count = ft_arg_count(av);
	if (echo_without_arg_behavior(av, arg_count, fd))
		return ;
	// Implemented indexs incremented by one to match the current command line
	i = 2; // set i to 1 instead of 2
	n_option = 0;
	if (ft_strcmp(av[2], "-n")) // set 1 instead of 2
	{
		i = 3; // 2 instead of 3
		n_option = 1;
	}
	// printf("Count >> %d\n-n option = %d\n", arg_count, n_option);
	// i is set to one becuase the index 0 contains the command
	// echo; -n; aaa; bbb; ccc;

	while (av[i])
	{
		len = ft_strlen(av[i]);
		write(fd, av[i], len);
		if (i < (arg_count - 1))
			write(1, " ", 1);
		else if (n_option == 0)
			write(fd, "\n", 1);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Need more args\n");
		return (0);
	}

	// fd_out value to determine
	int fd = 1;

	if (ft_strcmp(av[1], "echo"))
		 exec_echo_built_in(av, fd);

}