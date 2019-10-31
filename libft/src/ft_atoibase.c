/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 02:09:23 by pemora            #+#    #+#             */
/*   Updated: 2019/09/20 18:22:45 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_power(int nb, int power)
{
	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	return (nb * ft_power(nb, power - 1));
}

static int		base_size(const char *base)
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
			if (*(base + i) == *(base + j) && i == j)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (i);
}

static long		get_value_from_base(char c, const char *base)
{
	int	i;

	i = 0;
	if (c == '+' | c == '-')
		return (-1);
	while (*base)
	{
		if (*base == c)
			return (i);
		base++;
		i++;
	}
	return (-1);
}

static long		get_value(char c, int i, int nbase, const char *base)
{
	int n;

	n = get_value_from_base(c, base);
	n *= ft_power(nbase, i);
	return (n);
}

int				ft_atoibase(const char *s, const char *base)
{
	int		n;
	int		i;
	int		sign;

	n = 0;
	i = 0;
	sign = 1;
	if (base_size((char*)base) < 2)
		return (0);
	if (*s == '-')
		sign *= -1;
	if (*s == '-' || *s == '+')
		s++;
	while (*(s + i))
	{
		if (get_value(*(s + i), (((ft_strlen(s) - 1) - i)), base_size(base),
			base) > 2147483647 - n)
			return (-2147483648);
		if (get_value_from_base(*(s + i), base) == -1)
			return ('\0');
		n += get_value(*(s + i), (ft_strlen(s) - 1) - i, base_size(base), base);
		i++;
	}
	return (n * sign);
}
