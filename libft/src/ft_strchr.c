/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:26:32 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 15:46:42 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	chr;
	int		i;

	if (c > 255)
		return (NULL);
	chr = (char)c;
	i = 0;
	while (s[i] != chr && s[i])
		i++;
	if (s[i] == chr)
		return ((char*)&s[i]);
	return (NULL);
}
