/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vertices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:15:43 by cbenoit           #+#    #+#             */
/*   Updated: 2019/09/13 16:35:03 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
#include <stdlib.h>

static int		add_command(char line[])
{
	int	i;

	i = 0;
	while (i < 2 && ft_strcmp(line, (((char*[2]){"start", "end"})[i])) != SAME)
		i++;
	return (i);
}

static int		add_vertex(char line[], t_parser_graph *graph, int *command_nb)
{
	if (graph->start->vertex.name == NULL)
		graph->start->vertex.name = pars_name(line);
	else if (add_elem(&graph->end, line) == FAILURE)
	{
		free(line);
		line = NULL;
		return (set_msg(FAILURE, graph, MALLOC_ERROR));
	}
	if (graph->end->vertex.name == NULL)
		return (0);
	if (check_vertex_dup(graph->start, graph->end->vertex.name))
	{
		free(graph->end->vertex.name);
		graph->end->vertex.name = NULL;
		return (0);
	}
	if (*command_nb == 0)
		graph->commands.s = graph->end->vertex.nb;
	else if (*command_nb == 1)
		graph->commands.t = graph->end->vertex.nb;
	*command_nb = 2;
	return (1);
}

static void		treat_instruction(t_parser_graph *graph, char *line,
				int *command_nb_tmp, int *command_nb)
{
	if (line[1] == '#')
	{
		if ((*command_nb_tmp = add_command(&line[2])) < 2)
			if (*command_nb < 2 || !(graph->parsing_list_end
			= add_pars_elem(graph->parsing_list_end, line)))
				graph->msg = (*command_nb < 2) ?
				"Error : wrong start or end room" : MALLOC_ERROR;
			*command_nb = *command_nb_tmp;
	}
	else if (!(graph->parsing_list_end =
	add_pars_elem(graph->parsing_list_end, line)))
		graph->msg = MALLOC_ERROR;
}

static char		*vertices_error(t_parser_graph *graph, int gnl_ret, char *line)
{
	if (gnl_ret == -1)
		return (set_null_msg(graph, "Error : read"));
	if (!line)
		return (set_null_msg(graph, "Error : there's no edge"));
	return (line);
}

char			*pars_vertices(t_parser_graph *graph)
{
	char	*line;
	int		command_nb;
	int		command_nb_tmp;
	int		gnl_ret;

	command_nb = 2;
	while ((gnl_ret = get_next_line(STDIN, &line) == 1))
	{
		if (line[0] == '#')
			treat_instruction(graph, line, &command_nb_tmp, &command_nb);
		else if (line[0] == 'L')
			graph->msg = "Error : illegal room name";
		else if (add_vertex(line, graph, &command_nb) == 0)
			return(line);
		else if (!(graph->parsing_list_end =
		add_pars_elem(graph->parsing_list_end, line)))
			graph->msg = MALLOC_ERROR;
		free(line);
		if (ft_strcmp(graph->msg, "OK") != 0)
			return (NULL);
		line = NULL;
	}
	return (vertices_error(graph, gnl_ret, line));
}
