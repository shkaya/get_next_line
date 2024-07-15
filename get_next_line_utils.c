/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuntakaya <shuntakaya@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:35:27 by shuntakaya        #+#    #+#             */
/*   Updated: 2024/05/16 14:35:28 by shuntakaya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	total;
	int		i;
	int		j;

	if (s1 == (char const *)0 || s2 == (char const *)0)
		return ((char *)0);
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *)malloc(total * sizeof(char));
	if (p == NULL)
		return ((char *)0);
	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		p[i++] = s2[j++];
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(const char *s1)
{
	size_t	total;
	char	*p;
	int		i;

	total = ft_strlen(s1) + 1;
	p = (char *)malloc(total * sizeof(char));
	if (p == NULL)
		return ((char *)0);
	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c || *s == c - 256 || *s == c + 256)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return ((char *)0);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	if (d < s)
	{
		while (n--)
		{
			*d++ = *s++;
		}
	}
	else if (d > s)
	{
		d += (n - 1);
		s += (n - 1);
		while (n--)
		{
			*d-- = *s--;
		}
	}
	return (dest);
}
