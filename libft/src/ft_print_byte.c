/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_byte.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:51:06 by coremart          #+#    #+#             */
/*   Updated: 2019/03/08 02:25:06 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursion(const unsigned char byte, const unsigned base,
		unsigned int nb_digit)
{
	if (base > 36 || base < 2)
		return ;
	if (byte >= base)
		recursion(byte / base, base, ++nb_digit);
	else if (base == 2)
		ft_putnchar(8 - nb_digit, '0');
	else if (base == 3)
		ft_putnchar(6 - nb_digit, '0');
	else if (base < 7)
		ft_putnchar(4 - nb_digit, '0');
	else
		ft_putnchar(2 - nb_digit, '0');
	ft_putchar(48 + byte % base + ((byte % base > 9) ? 39 : 0));
}

void		ft_print_byte(const unsigned char byte, const unsigned int base)
{
	recursion(byte, base, 1);
}
