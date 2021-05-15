/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:37:52 by dcho              #+#    #+#             */
/*   Updated: 2020/11/12 18:14:07 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
