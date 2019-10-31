/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <cbenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 20:51:06 by cbenoit           #+#    #+#             */
/*   Updated: 2019/10/18 11:29:41 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strrev(char *s)
{
	int		i;
	int		len;
	char	swap;

	i = -1;
	len = ft_strlen(s) - 1;
	while (++i <= len / 2)
	{
		swap = *(s + i);
		*(s + i) = *(s + (len - i));
		*(s + (len - i)) = swap;
	}
	return (s);
}

static int	base_size(const char *base)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (*(base + i))
	{
		if (*(base + i) == '+' || *(base + i) == '-')
			return (0);
		while (*(base + j))
		{
			if (j == i)
				j++;
			if (*(base + i) == *(base + j) && j == 1)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (i);
}

char		*ft_itoabase(int n, const char *base)
{
	char	*res;
	int		i;
	long	n2;

	if (base_size(base) < 2)
		return ("\0");
	res = ft_strnew(33);
	i = 0;
	n2 = n;
	if (n < 0)
		n2 = n * -1;
	while ((n2 / base_size(base)) > 0)
	{
		*(res + i) = *(base + (n2 % base_size(base)));
		n2 /= base_size(base);
		i++;
	}
	*(res + i) = *(base + (n2 % base_size(base)));
	i++;
	if (n < 0)
		*(res + i++) = '-';
	ft_strrev(res);
	return (res);
}
