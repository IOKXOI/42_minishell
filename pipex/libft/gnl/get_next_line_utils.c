/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:37:38 by sydauria          #+#    #+#             */
/*   Updated: 2022/08/26 07:37:02 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "../libft.h"

void	*free_all_fd(char **remainder)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		if (remainder[i])
		{
			free(*(remainder + i));
			*(remainder + i) = NULL;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_and_free(char *line, char *temp)
{
	char	*new_line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!line)
		return (temp);
	if (!temp)
		return (NULL);
	new_line = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(temp) + 1));
	if (!new_line)
		return (NULL);
	while (*(line + i))
		*(new_line + (j++)) = *(line + (i++));
	free(line);
	i = 0;
	while (*(temp + i))
		*(new_line + (j++)) = *(temp + (i++));
	free(temp);
	new_line[j] = '\0';
	return (new_line);
}
