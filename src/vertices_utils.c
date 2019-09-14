/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:57:19 by coremart          #+#    #+#             */
/*   Updated: 2019/09/14 17:30:49 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

char				*pars_name(char *line)
{
	int		i;
	int		j;

	i = 0;
	while (line[i] && line[i] != ' ')
		if (line[i++] == '-')
			return (NULL);
	if (line[i] == '\0')
		return (NULL);
	j = i + 1;
	while (ft_isdigit(line[j]))
		j++;
	if (line[j] != ' ' || !ft_isdigit(line[j - 1]))
		return (NULL);
	j++;
	while (ft_isdigit(line[j]))
		j++;
	if (line[j] != '\0' || !ft_isdigit(line[j - 1]))
		return (NULL);
	return (ft_strndup(line, i));
}

int				get_vertex(char *str, t_vertex_list *start)
{

	while (start->vertex.name && ft_strcmp(start->vertex.name, str) != SAME)
		start = start->next;
	if (start->vertex.name == NULL)
		return (-1);
	return (start->vertex.nb);
}
