/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 05:51:09 by coremart          #+#    #+#             */
/*   Updated: 2019/02/17 06:12:29 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long	ft_pwr(unsigned long nb, unsigned int exp)
{
	if (!exp)
		return (1);
	if (exp == 1)
		return (nb);
	if (exp % 2)
		return (nb * ft_pwr(nb * nb, (exp - 1) / 2));
	return (ft_pwr(nb * nb, exp / 2));
}
