/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:37:03 by coremart          #+#    #+#             */
/*   Updated: 2019/09/04 20:10:10 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

#include <stdio.h>

static inline t_edge	make_edge(unsigned int from, unsigned int to)
{
	return ((t_edge){from, to, 0});
}

/*
**	Create a vertex composed of 2 vertex like
**	this : vertex_in <-> vertex_out. To make the vertices the ones with
**	capacities no more the edges
*/
void					new_vertex(t_graph *graph, unsigned int vertex)
{
	unsigned int to;

	to = graph->nb_vertices - vertex - 1;
	push_back_adj_edges(&graph->adj_arr[vertex], graph->i);
	graph->edge_arr[graph->i] = make_edge(vertex, to);
	++graph->i;
	push_back_adj_edges(&graph->adj_arr[to], graph->i);
	graph->edge_arr[graph->i] = make_edge(to, vertex);
	++graph->i;
}

/*
**	Add the index of the edge in adj_arr and put the edge in edge_arr
*/
void					add_edge(t_graph *graph, unsigned int from, unsigned int to)
{
	if (graph->adj_arr[from].nb_edges == 0)
		new_vertex(graph, from);
	from = graph->nb_vertices - from - 1;
	if (graph->adj_arr[to].nb_edges == 0)
		new_vertex(graph, to);
	push_back_adj_edges(&graph->adj_arr[from], graph->i);
	graph->edge_arr[graph->i] = make_edge(from, to);
	++graph->i;
	push_back_adj_edges(&graph->adj_arr[to], graph->i);
	graph->edge_arr[graph->i] = make_edge(to, from);
	++graph->i;
}

void					rm_edge(t_graph *graph, unsigned int from, unsigned int to)
{
	rm_adj_edge(graph, &graph->adj_arr[from], to);
	rm_adj_edge(graph, &graph->adj_arr[to], from);
}
