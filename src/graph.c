/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:48:50 by coremart          #+#    #+#             */
/*   Updated: 2019/07/08 04:55:48 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdlib.h>

void	init_graph(t_graph *graph, int nb_vertices, int nb_edges)
{
	nb_vertices <<= 1;
	graph->nb_vertices = nb_vertices;
	graph->edge_arr = (t_edge*)malloc((nb_vertices + (nb_edges << 1)) * sizeof(t_edge));
	graph->i = 0;
	graph->adj_arr = (t_adj_edges*)malloc(nb_vertices * sizeof(t_adj_edges));
	graph->level_arr = (int*)malloc(nb_vertices * sizeof(int));
	while (nb_vertices--)
		init_adj_edges(&graph->adj_arr[nb_vertices]);
}

void	free_graph(t_graph *graph)
{
	int			i;
	t_adj_edges	adj_array;

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
