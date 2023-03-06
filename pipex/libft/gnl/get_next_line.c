/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:04:39 by sydauria          #+#    #+#             */
/*   Updated: 2022/09/23 23:07:34 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "../libft.h"

static ssize_t	create_and_fill_buffer(int fd, char **buffer)
{
	ssize_t	nb;

	buffer[fd] = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer[fd])
		return (-1);
	nb = read(fd, buffer[fd], BUFFER_SIZE);
	if (nb < 1)
		return (nb);
	buffer[fd][nb] = '\0';
	return (nb);
}

static char	*stop_condition(int fd, ssize_t nb, char *valid_line, char **buffer)
{
	if (nb < 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		if (valid_line)
			free(valid_line);
		return (NULL);
	}
	if (nb == 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (valid_line);
}

static char	*extract_str(char *buffer, ssize_t *new_line)
{
	char	*extracted;
	size_t	i;

	i = 0;
	while (*(buffer + (i + 1)) && *(buffer + i) != '\n')
		i++;
	if (*(buffer + i) == '\n')
		*new_line = TRUE;
	extracted = ft_strndup(buffer, i);
	if (!extracted)
		return (NULL);
	ft_memmove(buffer, (buffer + (i + 1)), ft_strlen((buffer + i)));
	return (extracted);
}

static char	*get_remainder(ssize_t *problem, ssize_t *exit_loop, char *buffer)
{
	char	*new_remainder;

	if (!*buffer)
	{
		free(buffer);
		return (NULL);
	}
	new_remainder = ft_strndup(buffer, BUFFER_SIZE);
	if (!new_remainder)
	{
		*problem = -1;
		*exit_loop = TRUE;
		return (NULL);
	}
	free(buffer);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	char		*valid_line;
	char		*temp;
	static char	*buffer[1024];
	ssize_t		nb;
	ssize_t		new_line;

	new_line = FALSE;
	valid_line = NULL;
	nb = 2;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (free_all_fd(buffer));
	while (!new_line)
	{
		if (!buffer[fd])
			nb = create_and_fill_buffer(fd, buffer);
		if (nb < 1)
			return (stop_condition(fd, nb, valid_line, buffer));
		temp = extract_str(buffer[fd], &new_line);
		valid_line = ft_strjoin_and_free(valid_line, temp);
		if (!valid_line)
			return (stop_condition(fd, -1, valid_line, buffer));
		buffer[fd] = get_remainder(&nb, &new_line, buffer[fd]);
	}
	return (stop_condition(fd, nb, valid_line, buffer));
}
