/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:15:42 by dcho              #+#    #+#             */
/*   Updated: 2021/02/01 23:59:16 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	i;
	size_t	len;

	len = ft_strlen(s1);
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		*(res + i) = *(s1 + i);
		i++;
	}
	*(res + i) = 0;
	return (res);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		*((unsigned char*)b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		dst_len;
	size_t		src_len;
	size_t		i;
	size_t		result;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	while (i + 1 < size && *src)
	{
		*(dst + i) = *src++;
		i++;
	}
	if (size != 0)
		*(dst + i) = 0;
	if (size < dst_len)
		result = src_len + size;
	else
		result = src_len + dst_len;
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	s1len;
	size_t	s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(s = malloc(sizeof(char) * s1len + sizeof(char) * s2len + 1)))
		return (NULL);
	ft_memset(s, 0, s1len + s2len + 1);
	ft_strlcat(s, s1, s1len + 1);
	ft_strlcat(s, s2, s1len + s2len + 1);
	return (s);
}
