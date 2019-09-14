/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:56:02 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 13:57:01 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		i;
	int		size;

	sign = 0;
	i = 0;
	if (n < 0)
		sign = 1;
	size = ft_count_digit(n) + sign;
	if (!(str = ft_strnew(size)))
		return (NULL);
	if (sign)
	{
		str[i++] = '-';
		if (n == -2147483648)
			return (ft_strcpy(str, "-2147483648"));
		n *= -1;
	}
	while (size - sign)
	{
		str[--size] = (char)(n % 10 + '0');
		n /= 10;
	}
	return (str);
}
