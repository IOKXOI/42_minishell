/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:14:22 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:10:50 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
	{
		perror("ft_strjoin : malloc");
		return (NULL);
	}
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	if (j > 0)
		s3[j] = '\0';
	else
		return (free(s3), ft_strdup(" \0"));
	return (s3);
}

char	*ft_join_and_free_1(char *s1, char *s2, int a, int b)
{
	char	*s3;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (perror("ft_strjoin : malloc"), NULL);
	while (s1[i])
		s3[j++] = s1[i++];
	if (a == 1)
		free(s1);
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j] = '\0';
	if (b == 1)
		free(s2);
	return (s3);
}
