/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 02:16:35 by coremart          #+#    #+#             */
/*   Updated: 2019/09/13 06:31:02 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include "libft.h"
// #include <unistd.h>
// #include <limits.h>
// #include <stdlib.h>

void				add_str(t_buff_printer *buff, char *str)
{
	int	len;

	if ((len = ft_strlen(str)) >= LEM_IN_BUFF_SIZE - buff->index)
	{
		write(1, buff->buff, buff->index);
		buff->index = 0;
	}
	ft_strcpy(&buff->buff[buff->index], str);
	buff->index += len;
}

char				*get_name(t_vertex_list *list, int vertex)
{
	while (vertex--)
		list = list->next;
	return (list->vertex.name);
}

static void			add_offset(int *offset_arr, int offset)
{
	while (offset_arr[0] != INT_MAX)
		offset_arr++;
	offset_arr[0] = offset;
	offset_arr[1] = INT_MAX;
}

static int			get_offset(int *offset_arr, int nb)
{
	int i;

	i = 0;
	while (nb > offset_arr[i])
		i++;
	return (i);
}

static int			add_nb_lines(t_parser_graph *p_graph,
					t_buff_printer *buff)
{
	char	*tmp;

	if (p_graph->flag[BONUS_C])
		add_str(buff, COLOR_GREEN);
	add_str(buff, "\nTotal lines: ");
	if (!(tmp = ft_itoa(p_graph->nb_lines)))
		return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
	add_str(buff, tmp);
	free(tmp);
	add_str(buff, "\n");
	return (SUCCESS);
}

static int			print_ants_state(t_parser_graph *p_graph,
					t_buff_printer *buff)
{
	char	*tmp;

	add_str(buff, COLOR_RED);
	add_str(buff, "Line ");
	if (!(tmp = ft_itoa(p_graph->nb_lines + 1)))
		return (FAILURE);
	add_str(buff, tmp);
	free(tmp);
	add_str(buff, " : ");
	add_str(buff, COLOR_YELLOW);
	add_str(buff, "ants_waiting ");
	if (!(tmp = ft_itoa(p_graph->ants - p_graph->ants_on_rooms)))
		return (FAILURE);
	add_str(buff, tmp);
	free(tmp);
	add_str(buff, ", ants_on ");
	if (!(tmp = ft_itoa(p_graph->ants_on_rooms - p_graph->ants_at_end)))
		return (FAILURE);
	add_str(buff, tmp);
	free(tmp);
	add_str(buff, ", ants_end ");
	if (!(tmp = ft_itoa(p_graph->ants_at_end)))
		return (FAILURE);
	add_str(buff, tmp);
	free(tmp);
	add_str(buff, "\n");
	return (SUCCESS);
}

int					print_one_line(t_paths *paths, t_parser_graph *p_graph,
					t_buff_printer *buff)
{
	char			*tmp;
	int				i;

	i = 0;
	while (i++ < paths->paths->ants_on)
	{
		if (!(tmp = ft_itoa(i)))
			return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
		add_str(buff, "L");
		add_str(buff, tmp);
		free(tmp);
		add_str(buff, "-");
		add_str(buff, get_name(p_graph->start, p_graph->commands.t));
		add_str(buff, " ");
		p_graph->ants_at_end++;
	}
	buff->buff[buff->index - 1] = '\n';
	p_graph->nb_lines = 1;
	if (p_graph->flag[BONUS_P] && print_paths(p_graph, *paths, buff)
	== FAILURE)
		return (FAILURE);
	if (p_graph->flag[BONUS_N] && add_nb_lines(p_graph, buff) == FAILURE)
		return (FAILURE);
	write(1, buff->buff, buff->index);
	return (SUCCESS);
}

static int			add_op(t_paths *paths, int *offset_arr,
					t_parser_graph *p_graph, t_buff_printer *buff)
{
	char	*tmp;

	if (!(tmp = ft_itoa(paths->size * (p_graph->line
	- p_graph->cur_vertex) + p_graph->cur_path + 1
	- get_offset(offset_arr, paths->size
	* (p_graph->line - p_graph->cur_vertex) + p_graph->cur_path))))
	{
		free(offset_arr);
		return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
	}
	add_str(buff, "L");
	add_str(buff, tmp);
	free(tmp);
	add_str(buff, "-");
	if (p_graph->cur_vertex == paths->paths[p_graph->cur_path].len)
	{
		add_str(buff, get_name(p_graph->start, p_graph->commands.t));
		p_graph->ants_at_end++;
	}
	else
		add_str(buff, get_name(p_graph->start,
		paths->paths[p_graph->cur_path].path[p_graph->cur_vertex]));
	if (p_graph->cur_vertex == 0)
		p_graph->ants_on_rooms++;
	add_str(buff, " ");
	return (SUCCESS);
}

static int			print_cur_vertex(t_paths *paths, int *offset_arr,
					t_parser_graph *p_graph, t_buff_printer *buff)
{
	p_graph->cur_path = -1;
	while (++p_graph->cur_path < paths->size)
	{
		if (p_graph->cur_vertex > paths->paths[p_graph->cur_path].len)
			continue ;
		if (p_graph->line - p_graph->cur_vertex
		>= paths->paths[p_graph->cur_path].ants_on)
		{
			if (p_graph->cur_vertex == 0)
				add_offset(offset_arr, paths->size *
				(p_graph->line - p_graph->cur_vertex) + p_graph->cur_path);
		}
		else if (add_op(paths, offset_arr, p_graph, buff) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static inline int	print_line(t_parser_graph *p_graph, int *offset_arr,
					t_buff_printer *buff, t_paths *paths)
{
	p_graph->cur_vertex = p_graph->line + 1;
	if (p_graph->flag[BONUS_D] && print_ants_state(p_graph, buff) == FAILURE)
	{
		free(offset_arr);
		return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
	}
	while (p_graph->cur_vertex--)
		if (print_cur_vertex(paths, offset_arr, p_graph, buff) != SUCCESS)
			return (FAILURE);
	if (buff->index > 0 && buff->buff[buff->index - 1] == ' ')
		buff->index--;
	add_str(buff, "\n");
	p_graph->nb_lines += 1;
	return (SUCCESS);
}

int					print_res(t_parser_graph *p_graph, t_paths *paths)
{
	int				*offset_arr;
	t_buff_printer	buff;

	buff.index = 0;
	if (paths->paths[0].len == 0)
		return (print_one_line(paths, p_graph, &buff));
	if (!(offset_arr = (int*)malloc(sizeof(int)
	* (paths->paths[0].ants_on + paths->paths[0].len + 1)
	* ((paths->paths[0].ants_on + paths->paths[0].len) >> 1))))
		return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
	offset_arr[0] = INT_MAX;
	p_graph->line = -1;
	while (++p_graph->line < paths->paths[0].ants_on + paths->paths[0].len)
		if (print_line(p_graph, offset_arr, &buff, paths) != SUCCESS)
			return (FAILURE);
	free(offset_arr);
	if (p_graph->flag[BONUS_P] && print_paths(p_graph, *paths, &buff)
	== FAILURE)
		return (FAILURE);
	if (p_graph->flag[BONUS_N] && add_nb_lines(p_graph, &buff) == FAILURE)
		return (FAILURE);
	write(1, buff.buff, buff.index);
	return (SUCCESS);
}
