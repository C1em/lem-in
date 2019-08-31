/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:37:03 by coremart          #+#    #+#             */
/*   Updated: 2019/08/31 13:48:46 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

#include <stdio.h>

static t_edge	make_edge(int from, int to, int capacity)
{
	t_edge	edge;

	edge.from_vertex = from;
	edge.to_vertex = to;
	edge.flow = 0;
	edge.capacity = capacity; //?????? capcity always = 1
	return (edge);
}

/*
**	Create a vertex composed of 2 vertex like
**	this : vertex_in <-> vertex_out. To make the vertices the ones with
**	capacities no more the edges
*/
void			new_vertex(t_graph *graph, int vertex)
{
	int to;

	to = graph->nb_vertices - vertex - 1;
	push_back_adj_edges(&graph->adj_arr[vertex], graph->i);
	graph->edge_arr[graph->i] = make_edge(vertex, to, 1);
	++graph->i;
	push_back_adj_edges(&graph->adj_arr[to], graph->i);
	graph->edge_arr[graph->i] = make_edge(to, vertex, 1);
	++graph->i;
}

/*
**	Add the index of the edge in adj_arr and put the edge in edge_arr
*/
void			add_edge(t_graph *graph, int from, int to, int s)
{
	if (!s)
	{
		if (graph->adj_arr[from].nb_edges == 0)
			new_vertex(graph, from);
		from = graph->nb_vertices - from - 1;
	}
	if (graph->adj_arr[to].nb_edges == 0)
		new_vertex(graph, to);
	push_back_adj_edges(&graph->adj_arr[from], graph->i);
	graph->edge_arr[graph->i] = make_edge(from, to, 1);
	++graph->i;
	push_back_adj_edges(&graph->adj_arr[to], graph->i);
	graph->edge_arr[graph->i] = make_edge(to, from, 1);
	++graph->i;
}

void			rm_edge(t_graph *graph, int from, int to)
{
	rm_adj_edge(graph, &graph->adj_arr[from], to);
	rm_adj_edge(graph, &graph->adj_arr[to], from);
}

void		direct_edge(t_edge *edge_arr, int index)
{
	edge_arr[index ^ 1].capacity = 0;
}
