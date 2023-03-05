/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 01:12:36 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:12:48 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*newstr;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	len = ft_strlen(s1) - 1;
	if (i == (size_t)ft_strlen(s1))
		return (ft_strdup(""));
	else if (!set)
		return (ft_strdup((char *)s1));
	while (ft_strchr(set, s1[len]) && i < len)
		len--;
	newstr = malloc(sizeof(char) * (len + 2 - i));
	if (!newstr)
		return (NULL);
	while (i <= len)
		newstr[j++] = s1[i++];
	newstr[j] = '\0';
	return (newstr);
}
