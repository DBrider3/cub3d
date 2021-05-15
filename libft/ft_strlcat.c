/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:35:53 by dcho              #+#    #+#             */
/*   Updated: 2020/11/04 19:56:22 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
