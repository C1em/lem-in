/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:57:19 by coremart          #+#    #+#             */
/*   Updated: 2019/09/10 16:36:11 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include "libft.h"
// #include <stdlib.h>

static int				add_command(char line[])
{
	int	i;

	i = 0;
	while (i < 2 && ft_strcmp(line, (((char*[2]){"start", "end"})[i])) != SAME)
		i++;
	return (i);
}

char				*pars_name(char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i] && line[i] != ' ')
		if (line[i++] == '-')
			return (NULL);
	if (line[i] == '\0')
		return (NULL);
	j = i + 1;
	while (ft_isdigit(line[j]))
		j++;
	if (line[j] != ' ')
		return (NULL);
	j++;
	while (ft_isdigit(line[j]))
		j++;
	if (line[j] != '\0')
		return (NULL);
	return (ft_strndup(line, i));
}

static int				add_vertex(char line[], t_parser_graph *graph, int *command_nb)
{
	if (graph->start->vertex.name == NULL)
		graph->start->vertex.name = pars_name(line);
	else
		add_elem(&graph->end, line);
	if (*command_nb == 0)
		graph->commands.s = graph->end->vertex.nb;
	else if (*command_nb == 1)
		graph->commands.t = graph->end->vertex.nb;
	*command_nb = 2;
	if (graph->end->vertex.name == NULL)
		return (0);
	if (check_vertex_dup(graph->start, graph->end->vertex.name))
	{
		free(graph->end->vertex.name);
		graph->end->vertex.name = NULL;
		return (0);
	}
	return (1);
}

int				get_vertex(char *str, t_vertex_list *start)
{

	while (start->vertex.name && ft_strcmp(start->vertex.name, str) != SAME)
		start = start->next;
	if (start->vertex.name == NULL)
		return (-1);
	return (start->vertex.nb);

}

char		*pars_vertices(t_parser_graph *graph)
{
	char	*line;
	int		command_nb;
	int		gnl_ret;

	command_nb = 2;
	while ((gnl_ret = get_next_line(STDIN, &line) == 1))
	{
		if (line[0] == '#')
		{
			if (line[1] == '#')
			{
				if ((command_nb = add_command(&line[2])) < 2)
					graph->parsing_list_end = add_pars_elem(graph->parsing_list_end, line);
			}
			else
				graph->parsing_list_end = add_pars_elem(graph->parsing_list_end, line);
		}
		else if (add_vertex(line, graph, &command_nb) == 0)
			return(line);
		else
			graph->parsing_list_end = add_pars_elem(graph->parsing_list_end, line);
		free(line);
		line = NULL;
	}
	if (gnl_ret == -1)
		error_sys();
	return (line);
}
