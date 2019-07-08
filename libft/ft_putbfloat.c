/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbfloat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 22:24:47 by coremart          #+#    #+#             */
/*   Updated: 2019/03/08 02:26:21 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putbfloat(float nb)
{
	int		i;
	int		y;

	y = 4;
	while (y--)
	{
		i = 128;
		while (i)
		{
			if (*((unsigned char*)&nb + y) & i)
				ft_putchar('1');
			else
				ft_putchar('0');
			if (i == 128 && y > 1)
				ft_putchar(' ');
			i >>= 1;
		}
	}
	ft_putchar('\n');
}
