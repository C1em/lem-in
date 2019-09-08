/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:54:26 by coremart          #+#    #+#             */
/*   Updated: 2019/09/08 04:19:25 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"
#include <stdlib.h>

static void		add_edge(t_parser_graph *p_graph, char *line)
{
	char	*str;
	int		vertex;
	int		vertex_2;

	str = line;
	while (str[0] && str[0] != '-')
		str++;
	str[0] = '\0';
	str++;
	vertex = get_vertex(line, p_graph->start);
	vertex_2 = get_vertex(str, p_graph->start);
	p_graph->matrix[vertex][vertex_2] = NO_FLOW;
	p_graph->matrix[vertex_2][vertex] = NO_FLOW;
	p_graph->adj_edges_count[vertex]++;
	p_graph->adj_edges_count[vertex_2]++;
}

void			pars_edges(t_parser_graph *p_graph, char *line)
{
	int		size;

	size = p_graph->end->vertex.nb;
	if (!(p_graph->matrix = (int**)malloc(sizeof(int*) * size)))
		exit(1);
	if (!(p_graph->adj_edges_count = (int*)malloc(sizeof(int) * size)))
		exit(1);
	ft_bzero(p_graph->adj_edges_count, sizeof(int) * size);
	while (size--)
	{
		if (!(p_graph->matrix[size] = (int*)malloc(sizeof(int) * p_graph->end->vertex.nb)))
			exit(1);
		ft_bzero(p_graph->matrix[size], sizeof(int) * p_graph->end->vertex.nb);
	}
	add_edge(p_graph, line);
	free(line);
	while (get_next_line(STDIN, &line) == 1)
	{
		if (line[0] == '#')
			add_comment(line);
		else
			add_edge(p_graph, line);
		free(line);
	}
}
