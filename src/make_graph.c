/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 07:51:45 by coremart          #+#    #+#             */
/*   Updated: 2019/09/14 17:26:46 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
#include <stdlib.h>

t_graph		*make_graph(t_parser_graph *p_graph)
{
	t_graph	*graph;

	if (!(graph = (t_graph*)malloc(sizeof(t_graph))))
		return ((t_graph *)set_null_msg(p_graph, MALLOC_ERROR));
	graph->size = p_graph->end->vertex.nb; // maybe + 1 ???????
	if (!(graph->flow_arr = (int*)malloc(sizeof(int) * graph->size)))
	{
		free(graph);
		return ((t_graph *)set_null_msg(p_graph, MALLOC_ERROR));
	}
	ft_bzero(graph->flow_arr, sizeof(int) * graph->size);
	if (!(graph->level_arr = (int*)malloc(sizeof(int) * graph->size)))
	{
		free(graph);
		free(graph->flow_arr);
		return ((t_graph *)set_null_msg(p_graph, MALLOC_ERROR));
	}
	graph->adj_matrix = p_graph->matrix;
	graph->adj_edges_arr = p_graph->adj_edges_count;
	graph->s_t = p_graph->commands;
	graph->ants = p_graph->ants;
	return (graph);
}
