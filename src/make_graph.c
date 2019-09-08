/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 07:51:45 by coremart          #+#    #+#             */
/*   Updated: 2019/09/08 05:22:18 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"
#include <stdlib.h>

t_graph		*make_graph(t_parser_graph *p_graph)
{
	t_graph	*graph;

	if (!(graph = (t_graph*)malloc(sizeof(t_graph))))
		exit(1);
	graph->size = p_graph->end->vertex.nb;
	if (!(graph->flow_arr = (int*)malloc(sizeof(int) * graph->size)))
		exit(1);
	ft_bzero(graph->flow_arr, sizeof(int) * graph->size);
	if (!(graph->level_arr = (int*)malloc(sizeof(int) * graph->size)))
		exit(1);
	graph->adj_matrix = p_graph->matrix;
	graph->adj_edges_arr = p_graph->adj_edges_count;
	graph->s_t = p_graph->commands;
	graph->ants = p_graph->ants;
	return (graph);
}
