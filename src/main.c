/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:52:16 by coremart          #+#    #+#             */
/*   Updated: 2019/07/08 07:16:28 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

#include <stdio.h>
#include <stdlib.h>

void	print_path(t_graph *graph, t_edge *edge, int t)
{
	int cur_vertex;
	int i;

	cur_vertex = edge->from_vertex;
	if (cur_vertex >= graph->nb_vertices >> 1)
		printf("vertex :%d out -> ", graph->nb_vertices - cur_vertex - 1);
	else
		printf("vertex :%d in -> ", cur_vertex);
	while (cur_vertex != t)
	{
		i = 0;
		while (graph->edge_arr[graph->adj_arr[cur_vertex].adj_index[i]].flow <= 0)
			i++;
		cur_vertex = graph->edge_arr[graph->adj_arr[cur_vertex].adj_index[i]].to_vertex;
		if (cur_vertex >= graph->nb_vertices >> 1)
			printf("vertex :%d out -> ", graph->nb_vertices - cur_vertex - 1);
		else
			printf("vertex :%d in -> ", cur_vertex);
	}
}

void	print_res(t_graph *graph, int s, int t)
{
	int i;
	t_edge *edge;

	i = 0;
	while (i < graph->adj_arr[s].nb_edges)
	{
		edge = &graph->edge_arr[graph->adj_arr[s].adj_index[i]];
		if (edge->flow > 0)
			print_path(graph, edge, t);
		printf("\n");
		++i;
	}
}

void	print_graph(t_graph *graph, int cur_vertex)
{
	t_queue_ptr	queue;
	t_queue		*tmp_elem;
	int			i;
	t_edge		*edge;
	int			cur_level;

	printf("%d\n", cur_vertex);
	init_queue(&queue);
	enqueue(&queue, cur_vertex);
	cur_level = graph->level_arr[cur_vertex];
	while (queue.size > 0)
	{
		tmp_elem = dequeue(&queue);
		cur_vertex = tmp_elem->value;
		free(tmp_elem);
		i = 0;
		if (graph->level_arr[cur_vertex] == cur_level + 1)
		{
			printf("\n");
			++cur_level;
		}
		while (i < graph->adj_arr[cur_vertex].nb_edges)
		{
			edge = &graph->edge_arr[graph->adj_arr[cur_vertex].adj_index[i]];
//			printf("level of %d :%d\n", edge->from_vertex, graph->level_arr[edge->from_vertex]);
//			printf("level of %d :%d\n", edge->to_vertex, graph->level_arr[edge->to_vertex]);
			if (graph->level_arr[edge->to_vertex] == cur_level + 1)
			{
				if (edge->to_vertex >= graph->nb_vertices >> 1)
					printf("|%d out", graph->nb_vertices - edge->to_vertex - 1);
				else
					printf("|%d in", edge->to_vertex);
				enqueue(&queue, edge->to_vertex);
			}
			++i;
		}
	}
	free_queue(&queue);
}


int main(void)
{
	int		nb_vertices;
	int		nb_edges;
	t_graph	graph;
	int		i;
	int		u;
	int		v;

/*	i = 0;
	printf("nb of vertices nb of edges\n");
	scanf("%d %d", &nb_vertices, &nb_edges);
	init_graph(&graph, nb_vertices + 2, nb_edges + 2);
	// add all the edges
	while (i < nb_edges)
	{
		printf("from to\n");
		scanf("%d %d", &u, &v);
		add_edge(&graph, u + 1, v + 1, 0);
		++i;
	}
	// connect the source
	printf("source\n");
	scanf("%d", &u);
	add_edge(&graph, 0, u + 1, 1);
	// connect the sink
	printf("sink\n");
	scanf("%d", &u);
	add_edge(&graph, u + 1, nb_vertices + 1, 1);
	graph.nb_vertices = nb_vertices + 2;
	printf("%d\n", get_max_flow(&graph, 0, nb_vertices + 1));*/


	init_graph(&graph, 12, 14);
	add_edge(&graph, 1, 2, 1);
	add_edge(&graph, 1, 3, 1);
	add_edge(&graph, 2, 0, 0);
	add_edge(&graph, 2, 4, 0);
	add_edge(&graph, 3, 0, 0);
	add_edge(&graph, 0, 8, 0);
	add_edge(&graph, 4, 10, 0);
	add_edge(&graph, 10, 6, 0);
	add_edge(&graph, 8, 5, 0);
	add_edge(&graph, 10, 5, 0);
	add_edge(&graph, 6, 11, 0);
	add_edge(&graph, 11, 7, 0);
	add_edge(&graph, 5, 9, 0);
	add_edge(&graph, 9, 7, 0);

	simplify_graph(&graph, 1);
//	print_graph(&graph, 1);
	printf("%d\n", get_max_flow(&graph, 1, 7));
	print_res(&graph, 1, 7);
/*	_____
   /  1	 \
  |	 / \ /
  |	2	3
   \|\
	0 4
	| |
	8 10
	|/|
	5 6
	| |
	9 11
	 \|
	  7
*/

	free_graph(&graph);
	return (0);
}
