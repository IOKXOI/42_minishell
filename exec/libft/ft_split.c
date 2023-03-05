/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:00:40 by sydauria          #+#    #+#             */
/*   Updated: 2022/08/26 07:35:43 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char sep)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (str[i] && str[i] != sep)
		words++;
	while (str[i])
	{
		if (str[i] == sep
			&& str[i + 1] != sep
			&& str[i + 1])
			words++;
		i++;
	}
	return (words);
}

static int	len_to_sep(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_strndup_split(const char *str, size_t n)
{
	char	*copy;
	size_t	i;

	copy = malloc((n + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (str[i] && n--)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static void	*free_all(char **tab, int i)
{
	while (i--)
		free(tab[i]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	tab = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	tab[count_words(s, c)] = NULL;
	while (*s)
	{
		while (*s == c)
			s++;
		len = len_to_sep((char *)s, c);
		if (len == 0)
			return (tab);
		tab[i] = ft_strndup_split(s, len);
		if (tab[i] == NULL)
			return (free_all(tab, i));
		s = (s + len);
		i++;
	}
	return (tab);
}
