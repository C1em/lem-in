/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:56:06 by coremart          #+#    #+#             */
/*   Updated: 2019/09/11 16:30:56 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include <stdlib.h>

t_vertex_list	*init_list(void)
{
	t_vertex_list	*list;

	if (!(list = (t_vertex_list*)malloc(sizeof(t_vertex_list))))
		return (NULL);
	list->next = NULL;
	list->vertex.name = NULL;
	list->vertex.nb = 0;
	return (list);
}

int				add_elem(t_vertex_list **end, char line[])
{
	if (!((*end)->next = (t_vertex_list*)malloc(sizeof(t_vertex_list))))
		return (FAILURE);
	(*end)->next->vertex.nb = (*end)->vertex.nb + 1;
	*end = (*end)->next;
	(*end)->vertex.name = pars_name(line);
	(*end)->next = NULL;
	return (SUCCESS);
}
