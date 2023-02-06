#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *buffer)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(buffer) + 1));
	if (!str)
		return (free(s1), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = -1;
	while (buffer[++j])
		str[i++] = buffer[j];
	str[i] = '\0';
	return (free(s1), str);
}

int main(int ac, char **av, char **envp)
{
    // char    *str;
    char    *path;
    int     fd;


    (void)av;
    (void)envp;
    if (ac != 1)
        return (printf("need 1 arg\n"), 1);
    // path = getcwd(NULL, 0);
    fd = chdir("/mnt/nfs/homes/caboudar");
    path = getcwd(NULL, 0);
    // fd = chdir("Desktop");
    // path = getcwd(NULL, 0);
    // fd = chdir("../../..");
    // path = getcwd(NULL, 0);

    printf("\nchdir return value >> %d\n", fd);
    printf("chdir path %s\n", path);
}