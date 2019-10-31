/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 17:48:37 by cbenoit           #+#    #+#             */
/*   Updated: 2019/09/20 18:30:51 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		display(int nb, char *str, char *result, int index)
{
	unsigned int	nbr;
	unsigned int	str_length;

	str_length = 0;
	while (str[str_length])
		str_length++;
	if (nb < 0)
	{
		result[index++] = '-';
		nbr = nb * -1;
	}
	else
		nbr = nb;
	if (nbr >= str_length)
		display(nbr / str_length, str, result, index - 1);
	result[index] = str[nbr % str_length];
	return (index);
}

static int		get_number_length(int number, char *base)
{
	int	length;
	int	base_length;

	base_length = 0;
	while (base[base_length])
		base_length++;
	length = 0;
	while (number >= base_length)
	{
		++length;
		number /= base_length;
	}
	return (++length);
}

char			*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char			*result;
	int				number;
	int				last_index;

	if (!nbr || !base_from || !base_to)
		return (0);
	number = ft_atoibase(nbr, base_from);
	result = malloc(sizeof(char) * get_number_length(number, base_to));
	last_index = display(number, base_to, result,
		get_number_length(number, base_to) - 1);
	result[last_index + 1] = '\0';
	return (result);
}
