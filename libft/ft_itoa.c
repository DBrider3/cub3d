/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:44:59 by dcho              #+#    #+#             */
/*   Updated: 2020/11/11 20:24:30 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned	ft_abs(int n)
{
	return (n > 0 ? n : -n);
}

char			*ft_itoa(int n)
{
	char		s[12];
	char		*ps;
	unsigned	un;

	ps = s + 11;
	*ps = 0;
	un = ft_abs(n);
	while (un)
	{
		*--ps = un % 10 + '0';
		un /= 10;
	}
	if (n < 0)
		*--ps = '-';
	else if (n == 0)
		*--ps = '0';
	return (ft_strdup(ps));
}
