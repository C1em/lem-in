/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:52:16 by coremart          #+#    #+#             */
/*   Updated: 2019/09/10 12:44:11 by coremart         ###   ########.fr       */
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
		printf("\tants on it : %d, path size :%d\n", paths.paths[i].ants_on, paths.paths[i].len);
		++i;
	}
	if (paths.paths[0].len == 0)
		printf("1 line\n");
	else
		printf("%d lines\n", paths.paths[0].ants_on + paths.paths[0].len);
}

int main(void)
{
	t_paths			paths;
	t_graph			*graph;
	t_parser_graph	*p_graph;

	p_graph = parser();
	check_graph(p_graph);
	print_parsing_list(p_graph->parsing_list_start);
	graph = make_graph(p_graph);
//	print_graph(graph, graph->s_t.s);
//	print_matrix(graph->adj_matrix, graph->size);
//	if (is_s_t_edge(graph))

	if ((paths = get_max_flow(graph)).paths == NULL)
		return (0);
//	print_paths(paths);
	print_res(p_graph, &paths);

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

// check malloc ??????
// parser option -v -l ??????
// parser instructions ?????
// parser errors cases ????
// bonus ?????????
// check hardly ????????
