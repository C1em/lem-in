/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:55:05 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 15:46:18 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	int		i;

	if (c > 255)
		return (NULL);
	chr = (char)c;
	i = ft_strlen(s);
	while (s[i] != chr && i > 0)
		i--;
	if (s[i] == chr)
		return ((char*)&s[i]);
	return (NULL);
}
