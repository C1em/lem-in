/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:54:26 by coremart          #+#    #+#             */
/*   Updated: 2019/09/14 17:26:22 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
#include <stdlib.h>

static int		add_edge(t_parser_graph *p_graph, char *line)
{
	char	*str;
	int		vertex;
	int		vertex_2;

	str = line;
	while (str[0] && str[0] != '-')
		str++;
	if (str[0] == '\0' || str[1] == '\0')
		return (0);
	str[0] = '\0';
	vertex = get_vertex(line, p_graph->start);
	vertex_2 = get_vertex(&str[1], p_graph->start);
	if (vertex == -1 || vertex_2 == -1 || vertex == vertex_2
	|| p_graph->matrix[vertex][vertex_2] == NO_FLOW
	|| p_graph->matrix[vertex_2][vertex] == NO_FLOW)
		return (0);
	p_graph->matrix[vertex][vertex_2] = NO_FLOW;
	p_graph->matrix[vertex_2][vertex] = NO_FLOW;
	p_graph->adj_edges_count[vertex]++;
	p_graph->adj_edges_count[vertex_2]++;
	str[0] = '-';
	return (1);
}

static int		parse_edges_body(t_parser_graph *p_graph, char *line)
{
	if (line[0] == '#')
	{
		if (line[1] != '#' && !(p_graph->parsing_list_end =
			add_pars_elem(p_graph->parsing_list_end, line)))
		{
			free(line);
			return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
		}
	}
	else if (add_edge(p_graph, line))
	{
		if (!(p_graph->parsing_list_end =
		add_pars_elem(p_graph->parsing_list_end, line)))
		{
			free(line);
			return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
		}
	}
	else
	{
		free(line);
		return (SUCCESS);
	}
	free(line);
	return (SUCCESS);
}

int				pars_edges(t_parser_graph *p_graph, char *line)
{
	int		gnl_ret;

	if (line == NULL)
		return (SUCCESS);
	if (add_edge(p_graph, line) == 0)
	{
		free(line);
		return (SUCCESS);
	}
	if (!(p_graph->parsing_list_end =
		add_pars_elem(p_graph->parsing_list_end, line)))
		return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
	free(line);
	while ((gnl_ret = get_next_line(STDIN, &line) == 1))
		if (parse_edges_body(p_graph, line) == FAILURE)
			return (FAILURE);
	if (gnl_ret == -1)
		return (set_msg(FAILURE, p_graph, "Error : read"));
	return (SUCCESS);
}
