/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 09:50:56 by coremart          #+#    #+#             */
/*   Updated: 2019/10/11 11:50:28 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isint(const char *str)
{
	int i;
	int sign;

	if (str == NULL || str[0] == '\0')
		return (0);
	i = 0;
	if ((sign = (str[0] == '-')))
		str++;
	while (str[0] == '0')
		str++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0' || !ft_isdigit(str[i - 1]) || i > 10)
		return (0);
	if (i < 10)
		return (1);
	if ((i = ft_strncmp(str, "214748364", 9)) > 0)
		return (0);
	if (i < 0)
		return (1);
	if (str[9] <= '7' + sign)
		return (1);
	return (0);
}
