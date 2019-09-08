/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:52:16 by coremart          #+#    #+#             */
/*   Updated: 2019/09/08 05:28:18 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

#include <stdio.h>
#include <stdlib.h>

void	print_path(t_graph *graph, int cur_vertex, int t)
{
	int next_vertex;
	int i;

	printf("vertex :%d -> ", cur_vertex);
	while (cur_vertex != t)
	{
		i = 0;
		while (graph->adj_matrix[cur_vertex][get_next_vertex(graph->adj_matrix[cur_vertex], i)] == NO_FLOW)
			i++;
		cur_vertex = get_next_vertex(graph->adj_matrix[cur_vertex], i);
		printf("vertex :%d -> ", cur_vertex);
	}
}

void	print_res(t_graph *graph)
{
	int	i;
	int	next_vertex;

	i = 0;
	while (i < graph->adj_edges_arr[graph->s_t.s])
	{
		next_vertex = get_next_vertex(graph->adj_matrix[graph->s_t.s], i);
		if (graph->adj_matrix[graph->s_t.s][next_vertex] == FLOW)
			print_path(graph, next_vertex, graph->s_t.t);
		printf("\n");
		++i;
	}
}

void	print_graph(t_graph *graph, int cur_vertex)
{
	t_queue_ptr	queue;
	int			i;
	int			cur_level;
	int			next_vertex;

	init_queue(&queue, cur_vertex);
	cur_level = graph->level_arr[cur_vertex];
	while (queue.start != NULL)
	{
		cur_vertex = dequeue(&queue);
		i = 0;
		if (graph->level_arr[cur_vertex] == cur_level + 1)
		{
			printf("\n");
			++cur_level;
		}
		while (i < graph->adj_edges_arr[cur_vertex])
		{
			next_vertex = get_next_vertex(graph->adj_matrix[cur_vertex], i);
//			printf("level of %d :%d\n", edge->from_vertex, graph->level_arr[edge->from_vertex]);
//			printf("level of %d :%d\n", edge->to_vertex, graph->level_arr[edge->to_vertex]);
			if (graph->level_arr[next_vertex] == cur_level + 1)
			{
					printf("|%d", next_vertex);
				enqueue(&queue, next_vertex);
			}
			++i;
		}
	}
	free_queue(&queue);
}


void	print_paths(t_paths paths)
{
	int i;
	int j;

	i = 0;
	while (i < paths.size)
	{
		j = 0;
		printf("path :   ");
		while (j < paths.paths[i].len)
		{
			printf("-> %d ", paths.paths[i].path[j]);
			++j;
		}
		printf("\tants on it : %d\n", paths.paths[i].ants_on);
		++i;
	}
}

int main(void)
{
//	int		nb_vertices;
//	int		nb_edges;
	t_graph	*graph;
//	int		i;
//	int		u;
//	int		v;

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
	printf("%d\n", get_max_flow(&graph, 0, nb_vertices + 1));
*/

	graph = parser();

/*	init_graph(&graph, 13, 16);

	add_edge(&graph, 1, 2);

	add_edge(&graph, 1, 12);
	add_edge(&graph, 12, 7);


	add_edge(&graph, 1, 3);
	add_edge(&graph, 2, 0);
	add_edge(&graph, 2, 4);
	add_edge(&graph, 3, 0);
	add_edge(&graph, 0, 8);
	add_edge(&graph, 4, 10);
	add_edge(&graph, 10, 6);
	add_edge(&graph, 8, 5);
	add_edge(&graph, 0, 10);
	add_edge(&graph, 6, 11);
	add_edge(&graph, 11, 7);
	add_edge(&graph, 5, 9);
	add_edge(&graph, 9, 7);

	make_source(&graph, 1);
*/

//	print_graph(graph, graph->s_t.s);
	t_paths paths;
//		print_matrix(graph->adj_matrix, graph->size);
	if ((paths = get_max_flow(graph)).paths == NULL && printf("no path !!!\n"))
		return (0);
	print_paths(paths);
//	print_res(&graph, 1, 7);

/*	,――――、
   /  1 ― 3
  |	 / \
  |	2	12
  | |\	 |
  | 0 4	 |
   \| |	 |
	8 10 |
	|\|	 |
	5 6	 |
	| |	 |
	9 11 |
	 \|	/
	  7
*/


//	free_graph(&graph);
	return (0);
}

void	print_matrix(int **matrix, int size)
{
	int i;
	int j;

	i = 0;
	printf("\t| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12|\n\n");
	while (i < size)
	{
		j = 0;
		printf("%d\t| ", i);
		while (j < size)
		{
			printf("%d | ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n\n");
}
