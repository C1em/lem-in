/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digitbase.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:21:06 by coremart          #+#    #+#             */
/*   Updated: 2019/02/24 16:27:45 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_count_digitbase(long nb, const int base)
{
	unsigned int res;

	res = 0;
	if (!nb)
		return (1);
	while (nb && ++res)
		nb /= (const long)base;
	return (res);
}
