/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:42:27 by coremart          #+#    #+#             */
/*   Updated: 2019/07/08 04:45:18 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include <limits.h>

# define INF INT_MAX

typedef struct	s_edge
{
	int	from_vertex;
	int	to_vertex;
	int	capacity; // always equal to 1 or INF ????????????
	int	flow;
}				t_edge;

/*
**	adj_index : the index of adjacents edge in edge_arr. ex : adj_index[1]
**				to take the index of the first adjacent edge
**
**	size_arr : size of the alloced adj_index. always greater than nb_edges
**				with the aim of have the space for all the edges.
**				only used during parsing
**
**	nb_edges : nb_of edges stored in adj_index
*/
typedef struct	s_adj_edges
{
	int	*adj_index;
	int	size_arr;	// ???????
	int	nb_edges;
}				t_adj_edges;

/*
**	adj_arr : all the adj_edges sort by vertex. ex : adj_arr[vertex]
**
**	edge_arr : all the edges order by the call to add_edge.
**				have to used with adj_arr[vertex].adj_index[1] to get
**				the index of the first adjancent edge of vertex in edge_arr
**
**	level_arr : level of the vertex. ex: level_arr[vertex] = 3;
**
**	nb_vertices : nb of vertices in the graph
*/
typedef struct	s_gragh
{
	t_adj_edges	*adj_arr;
	t_edge		*edge_arr;
	int			*level_arr;
	int			nb_vertices;
	int			i;
}				t_graph;

typedef struct	s_queue
{
	int				value;
	struct s_queue	*next;
}				t_queue;

typedef struct	s_queue_ptr
{
	t_queue	*start;
	t_queue	*end;
	int		size;
}				t_queue_ptr;

/*
**	graph.c
*/
void	init_graph(t_graph *graph, int nb_vertices, int nb_edges);
void	free_graph(t_graph *graph);

/*
**	adj_edges.c
*/
void	init_adj_edges(t_adj_edges *adj_edges);
void	push_back_adj_edges(t_adj_edges *adj_edges, int item);
void	rm_adj_edge(t_graph *graph, t_adj_edges *adj_edge, int to);

/*
**	edges.c
*/
void			add_edge(t_graph *graph, int from, int to, int s_or_t);
void			rm_edge(t_graph *graph, int from, int to);
void			direct_edge(t_edge *edge_arr, int index);

/*
**	max_flow.c
*/
int			get_max_flow(t_graph *graph, int s, int t);

/*
**	queue.c
*/
void	free_queue(t_queue_ptr *queue);
t_queue	*dequeue(t_queue_ptr *queue);
void	enqueue(t_queue_ptr *queue, int vertex);
void	init_queue(t_queue_ptr *queue);

/*
**	simplify_graph.c
*/
void	simplify_graph(t_graph *graph, int s);

#endif
