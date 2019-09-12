/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:52:16 by coremart          #+#    #+#             */
/*   Updated: 2019/09/12 12:48:46 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include <stdio.h>
// #include <stdlib.h>

void	print_path(t_graph *graph, int cur_vertex, int t)
{
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


int		print_graph(t_parser_graph *p_graph, t_graph *graph, int cur_vertex)
{
	t_queue_ptr	queue;
	int			i;
	int			cur_level;
	int			next_vertex;

	if (init_queue(&queue, cur_vertex) == FAILURE)
		return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
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
				if (enqueue(&queue, next_vertex) == FAILURE)
					return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
			}
			++i;
		}
	}
	free_queue(&queue);
	return (SUCCESS);
}

int			print_paths(t_parser_graph *p_graph, t_paths paths, t_buff_printer *buff)
{
	int		i;
	int		j;
	char	*tmp;
	i = 0;
	while (i < paths.size)
	{
		j = 0;
		add_str(buff, "\nPath ");
		if (!(tmp = ft_itoa(i + 1)))
			return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
		add_str(buff, tmp);
		free(tmp);
		add_str(buff, " :  ");
		add_str(buff, get_name(p_graph->start, 0));
		add_str(buff, " ");
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
		// printf("\tants on it : %d, path size :%d\n", paths.paths[i].ants_on, paths.paths[i].len);
		++i;
	}
	add_str(buff, "\n");
	write(1, buff->buff, buff->index);
	return (SUCCESS);
}

static int		disp_error(t_parser_graph *p_graph)
{
	if (ft_strcmp("OK", p_graph->msg) == SAME)
		ft_putendl("OK\n");
	else if (p_graph->flag[BONUS_V])
		ft_putendl(p_graph->msg);
	else
		ft_putendl("Error");
	return (0);
}

int			 	main(int ac, char **av)
{
	t_paths			paths;
	t_graph			*graph;
	t_parser_graph	*p_graph;

	p_graph = init_pars_graph();
	if (ac >= 1 && fill_option(p_graph, av) == FAILURE)
		return (ft_break(0, 1, "usage: ./lem-in [-cvnpdm]\n")); //-> free p_graph
	if (parser(p_graph) == FAILURE)
		return (disp_error(p_graph));//free p_graph
	if (p_graph->flag[BONUS_M])
		return (0); //free p_graph
	print_parsing_list(p_graph->parsing_list_start);
	if (!(graph = make_graph(p_graph)))
		return (disp_error(p_graph)); //free p_graph
	if ((paths = get_max_flow(p_graph, graph)).paths == NULL)
	{
		if (ft_strcmp("OK", p_graph->msg) == SAME)
			p_graph->msg = "Error : there's no valid path";
		return (disp_error(p_graph)); //free p_graph
	}

	// t_buff_printer buff;
	// buff.index = 0;
	// print_paths(p_graph, paths, &buff);

	// add the case where paths.paths[0].size == 0 (send all the ants in one line)
	if (print_res(p_graph, &paths) == FAILURE || p_graph->flag[BONUS_V])
		return (disp_error(p_graph));//free p_graph
//	free_graph(&graph);

	//free p_graph
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

//maps/checker/map.error18 -> fix parser disp ok instead of error idem 3 -> check if there's tube and/or path
//map error 8 -> un lien relié a lui meme = erreur ?
//maps/checker/map.error20 -> fix parser -> "error : malloc"
//bug -> maps/test_s_direct_3sortie -> 5 lignes distinct au lieu d'une ??????

// free all properly in get_max_flow ?????????
// parser instructions ?????
//suppr tous les printf du programme ????????????/


// change return 0 to return 1 if error ???????????

// bonus -c color ???????
// maybe bonus -d -> display number of ant on start, on the algo, on end ?????????????

// check hardly ????????

// bonus -n number of solution line -> done
// bonus -v verbose -> done
// bonus -m map checker -> done
// bonus -p path used -> done
