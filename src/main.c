/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:52:16 by coremart          #+#    #+#             */
/*   Updated: 2019/09/25 15:15:30 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"
#include <stdlib.h>
#include <unistd.h>

static int	print_head_of_paths(t_parser_graph *p_graph, t_buff_printer *buff,
			int i)
{
	char	*tmp;

	if (p_graph->flag[BONUS_C])
		add_str(buff, COLOR_RED);
	add_str(buff, "\nPath ");
	if (!(tmp = ft_itoa(i + 1)))
		return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
	add_str(buff, tmp);
	free(tmp);
	add_str(buff, " :  ");
	if (p_graph->flag[BONUS_C])
		add_str(buff, COLOR_YELLOW);
	add_str(buff, get_name(p_graph->start, 0));
	add_str(buff, " ");
	return (SUCCESS);
}

int			print_paths(t_parser_graph *p_graph, t_paths paths,
			t_buff_printer *buff)
{
	int		i;
	int		j;

	i = 0;
	while (i < paths.size)
	{
		if (print_head_of_paths(p_graph, buff, i) == FAILURE)
			return (FAILURE);
		j = 0;
		while (j <= paths.paths[i].len)
		{
			add_str(buff, "-> ");
			if (j == paths.paths[i].len)
				add_str(buff, get_name(p_graph->start, p_graph->commands.t));
			else
				add_str(buff, get_name(p_graph->start, paths.paths[i].path[j]));
			add_str(buff, " ");
			++j;
		}
		++i;
	}
	add_str(buff, "\n");
	return (SUCCESS);
}

void		free_paths(t_paths paths)
{
	if (paths.paths == NULL)
		return ;
	while (paths.size--)
		free(paths.paths[paths.size].path);
	free(paths.paths);
}

static int	disp_error(t_parser_graph *p_graph, t_graph *graph)
{
	if (p_graph->flag[BONUS_C])
		write(1, COLOR_LIGHT_RED, 8);
	if (ft_strcmp("OK", p_graph->msg) == SAME)
	{
		ft_putendl("OK");
		write(1, COLOR_RESET, 5);
		free_all(p_graph, graph);
		return (EXIT_SUCCESS);
	}
	else if (p_graph->flag[BONUS_V])
		ft_putendl(p_graph->msg);
	else
		ft_putendl("ERROR");
	if (p_graph->flag[BONUS_C])
		write(1, COLOR_RESET, 5);
	free_all(p_graph, graph);
	return (EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	t_paths			paths;
	t_graph			*graph;
	t_parser_graph	*p_graph;

	p_graph = init_pars_graph();
	if (ac >= 1 && fill_option(p_graph, av) == FAILURE)
		return (ft_break(EXIT_FAILURE, 1, "usage: ./lem-in [-cvnpdm]"));
	if (parser(p_graph) == FAILURE || p_graph->flag[BONUS_M])
		return (disp_error(p_graph, NULL));
	if (p_graph->flag[BONUS_C])
		write(1, COLOR_YELLOW, 8);
	print_parsing_list(p_graph->parsing_list_start);
	if (!(graph = make_graph(p_graph)))
		return (disp_error(p_graph, graph));
	paths = get_max_flow(p_graph, graph);
	if (print_res(p_graph, &paths) == FAILURE || p_graph->flag[BONUS_V])
		return (disp_error(p_graph, graph));
	free_paths(paths);
	free_all(p_graph, graph);
	return (EXIT_SUCCESS);
}
