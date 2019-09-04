/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:48:50 by coremart          #+#    #+#             */
/*   Updated: 2019/09/04 20:04:42 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

void	init_graph(t_graph *graph, unsigned int nb_vertices, unsigned int nb_edges)
{
	nb_vertices = (nb_vertices << 1);
	graph->nb_vertices = nb_vertices;
	if (!(graph->edge_arr = (t_edge*)malloc((nb_vertices + (nb_edges << 1))
						* sizeof(t_edge))))
		exit(1);
	graph->i = 0;
	if (!(graph->adj_arr = (t_adj_edges*)malloc(nb_vertices * sizeof(t_adj_edges))))
		exit(1);
	if (!(graph->level_arr = (unsigned int*)malloc(nb_vertices * sizeof(unsigned int))))
		exit(1);
	while (nb_vertices--)
		init_adj_edges(&graph->adj_arr[nb_vertices]);
}

void	free_graph(t_graph *graph)
{
	unsigned int	i;
	t_adj_edges		adj_array;

	free(graph->level_arr);
	free(graph->edge_arr);
	i = 0;
	while (i < graph->nb_vertices)
	{
		adj_array = graph->adj_arr[i];
		free(adj_array.adj_index);
		++i;
	}
	free(graph->adj_arr);
}

/*
**	fusion sink_in and sink_out :
**
**				\		/
**				 sink_in			\	/
**					|		->		sink
**				sink_out			/	\
**				/		\
*/
void	make_sink(t_graph *graph, unsigned int sink)
{
	unsigned int	i;
	t_adj_edges		*sink_out;
	t_adj_edges		*sink_in;

	i = 0;
	sink_out = &graph->adj_arr[graph->nb_vertices - sink - 1];
	sink_in = &graph->adj_arr[sink];
	while (i < sink_out->nb_edges)
	{
		if (graph->edge_arr[sink_out->adj_index[i]].to_vertex != sink)
		{
			push_back_adj_edges(sink_in, sink_out->adj_index[i]);
			graph->edge_arr[sink_out->adj_index[i]].from_vertex = sink;
			graph->edge_arr[sink_out->adj_index[i] ^ 1].to_vertex = sink;
		}
		++i;
	}
	rm_adj_edge(graph, sink_in, graph->nb_vertices - sink - 1);
}
