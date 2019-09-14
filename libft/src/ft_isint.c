/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 09:50:56 by coremart          #+#    #+#             */
/*   Updated: 2019/09/14 09:55:30 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isint(const char *str)
{
	int i;
	int sign;

	if (str == NULL)
		return (0);
	i = 0;
	if ((sign = (str[0] == '-')))
		str++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0' || !ft_isdigit(str[i - 1]) || i > 10)
		return (0);
	if (i < 10)
		return (1);
	if (str[0] > '2' || str[1] > '1' || str[2] > '4' || str[3] > '7'
	|| str[4] > '4' || str[5] > '8' || str[6] > '3' || str[7] > '6'
	|| str[8] > '4' || str[9] > '7' + sign)
		return (0);
	return (1);
}
