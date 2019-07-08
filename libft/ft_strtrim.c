/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:13:10 by coremart          #+#    #+#             */
/*   Updated: 2018/11/13 11:15:28 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		sp_start;
	int		sp_end;
	char	*str;

	sp_start = 0;
	sp_end = 0;
	if (s)
	{
		while (s[sp_start] == ' ' || s[sp_start] == '\n' || s[sp_start] == '\t')
			sp_start++;
		if (!(s[sp_start]))
		{
			str = (char*)malloc(1);
			str[0] = 0;
			return (str);
		}
		sp_end = ft_strlen(s) - 1;
		while (s[sp_end] == ' ' || s[sp_end] == '\n' || s[sp_end] == '\t')
			sp_end--;
		str = ft_strndup(&s[sp_start], sp_end - sp_start + 1);
		return (str);
	}
	return (NULL);
}
