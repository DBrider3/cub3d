/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:26:42 by dcho              #+#    #+#             */
/*   Updated: 2020/11/11 20:30:47 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		len;
	char		*res;
	int			idx;

	len = ft_strlen(s);
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (0);
	idx = 0;
	while (*(s + idx))
	{
		*(res + idx) = f(idx, *(s + idx));
		idx++;
	}
	*(res + idx) = 0;
	return (res);
}
