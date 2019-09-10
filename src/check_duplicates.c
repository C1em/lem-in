/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 06:09:31 by coremart          #+#    #+#             */
/*   Updated: 2019/09/10 16:33:13 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include "libft.h"

int		check_vertex_dup(t_vertex_list *list, char *last)
{
	while (list->next)
	{
		if (ft_strcmp(list->vertex.name, last) == SAME)
			return (1);
		list = list->next;
	}
	return (0);
}
