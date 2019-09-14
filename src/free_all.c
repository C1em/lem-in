/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 03:28:30 by coremart          #+#    #+#             */
/*   Updated: 2019/09/14 10:06:46 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdlib.h>

static void	free_pars_list(t_parsing_list *start)
{
	t_parsing_list *tmp;

	if (start == NULL)
		return ;
	while (start)
	{
		tmp = start;
		start = start->next;
		free(tmp->line);
		free(tmp);
	}
}

static void	free_vertex_list(t_vertex_list *start)
{
	t_vertex_list *tmp;

	if (start == NULL)
		return ;
	while (start->vertex.name)
	{
		tmp = start;
		start = start->next;
		free(tmp->vertex.name);
		free(tmp);
	}
	free(start);
}

void		free_parser_graph(t_parser_graph *p_graph)
{
	if (p_graph == NULL)
		return ;
	if (p_graph->adj_edges_count)
		free(p_graph->adj_edges_count);
	// free(p_graph->msg) ???????????
	free_vertex_list(p_graph->start);
	free_pars_list(p_graph->parsing_list_start);
	free(p_graph);
}

void		free_all(t_parser_graph *p_graph, t_graph *graph)
{
	free_parser_graph(p_graph);
	if (!graph)
		return ;
	if (graph->adj_matrix)
	{
		while (graph->size--)
			if (graph->adj_matrix[graph->size])
				free(graph->adj_matrix[graph->size]);
		free(graph->adj_matrix);
	}
	if (graph->flow_arr)
		free(graph->flow_arr);
	if (graph->level_arr)
		free(graph->level_arr);
	free(graph);
}
