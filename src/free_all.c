/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 03:28:30 by coremart          #+#    #+#             */
/*   Updated: 2019/09/15 13:58:08 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
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

	if (!start)
		return ;
//	start->vertex.name = NULL;
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
	if (!p_graph)
		return ;
	if (p_graph->adj_edges_count)
		free(p_graph->adj_edges_count);
	if (p_graph->matrix)
	{
		while (p_graph->end->vertex.nb--)
			if (p_graph->matrix[p_graph->end->vertex.nb])
				free(p_graph->matrix[p_graph->end->vertex.nb]);
		free(p_graph->matrix);
	}
	free_vertex_list(p_graph->start);
	free_pars_list(p_graph->parsing_list_start);
	free(p_graph);
}

void		free_all(t_parser_graph *p_graph, t_graph *graph)
{
	free_parser_graph(p_graph);
	if (!graph)
		return ;
	if (graph->flow_arr)
		free(graph->flow_arr);
	if (graph->level_arr)
		free(graph->level_arr);
	free(graph);
}
