/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:42:27 by coremart          #+#    #+#             */
/*   Updated: 2019/09/04 19:49:12 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include <limits.h>

# define INF UINT_MAX
# define SIZE_ARR 100

typedef struct	s_edge
{
	unsigned int	from_vertex;
	unsigned int	to_vertex;
	int				flow;
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
	unsigned int	*adj_index;
	unsigned int	size_arr;	// ???????
	unsigned int	nb_edges;
}				t_adj_edges;

/*
**	adj_arr : all the adj_edges sort by vertex. ex : adj_arr[vertex]
**
**	edge_arr : all the edges order by the call to add_edge.
**				have to be used with adj_arr[vertex].adj_index[1] to get
**				the index of the first adjacent edge of vertex in edge_arr
**
**	level_arr : level of the vertex. ex: level_arr[vertex] = 3;
**
**	nb_vertices : nb of vertices in the graph
*/
typedef struct	s_gragh
{
	t_adj_edges		*adj_arr;
	t_edge			*edge_arr;
	unsigned int	*level_arr;
	unsigned int	nb_vertices;
	unsigned int	i;
}				t_graph;

typedef struct	s_queue
{
	unsigned int	value;
	struct s_queue	*next;
}				t_queue;

typedef struct	s_queue_ptr
{
	t_queue	*start;
	t_queue	*end;
}				t_queue_ptr;

/*
**	path : array of the vertices forming the path (without s and t)
**
**	len : path's length or path's size
**
**	ants_on : nb of ants on the path for the best distribution
*/
typedef struct	s_path
{
	unsigned int	*path;
	unsigned int	len;
	unsigned int	ants_on;
}				t_path;

typedef struct	s_paths
{
	t_path			*paths;
	unsigned int	size;
}				t_paths;

/*
**	graph.c
*/
void			init_graph(t_graph *graph, unsigned int nb_vertices, unsigned int nb_edges);
void			free_graph(t_graph *graph);
void			make_sink(t_graph *graph, unsigned int sink);

/*
**	adj_edges.c
*/
void			init_adj_edges(t_adj_edges *adj_edges);
void			push_back_adj_edges(t_adj_edges *adj_edges, unsigned int item);
void			rm_adj_edge(t_graph *graph, t_adj_edges *adj_edge, unsigned int to);

/*
**	edges.c
*/
void			add_edge(t_graph *graph, unsigned int from, unsigned int to);
void			rm_edge(t_graph *graph, unsigned int from, unsigned int to);

/*
**	max_flow.c
*/
t_paths			get_max_flow(t_graph *graph, unsigned int s, unsigned int t, unsigned int ants);

/*
**	queue.c
*/
void			free_queue(t_queue_ptr *queue);
unsigned int	dequeue(t_queue_ptr *queue);
void			enqueue(t_queue_ptr *queue, unsigned int vertex);
void			init_queue(t_queue_ptr *queue, unsigned int vertex);

/*
**	simplify_graph.c
*/
void			simplify_graph(t_graph *graph, unsigned int s);

/*
**	paths.c
*/
t_paths			get_new_paths(t_graph *graph, unsigned int size, unsigned int s, unsigned int t);
void			dispatch_ants(t_paths paths, unsigned int ants);
int				is_worse_path(t_paths cur_paths,t_paths new_paths);
void			free_paths(t_paths paths);

/*
**	q_sort_paths.c
*/
void		q_sort_paths(t_paths paths);

#endif
