/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 02:16:35 by coremart          #+#    #+#             */
/*   Updated: 2019/09/11 16:03:21 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include "libft.h"
// #include <unistd.h>
// #include <limits.h>
// #include <stdlib.h>

static void	add_str(t_buff_printer *buff, char *str)
{
	int	len;
//	printf("%s", str);
	if ((len = ft_strlen(str)) >= LEM_IN_BUFF_SIZE - buff->index)
	{
		write(1, buff->buff, buff->index);
		buff->index = 0;
	}
	ft_strcpy(&buff->buff[buff->index], str);
	buff->index += len;
}

static char	*get_name(t_vertex_list *list, int vertex)
{
	while (vertex--)
		list = list->next;
	return (list->vertex.name);
}

void		add_offset(int *offset_arr, int offset)
{
	while (offset_arr[0] != INT_MAX)
		offset_arr++;
	offset_arr[0] = offset;
	offset_arr[1] = INT_MAX;
}

int			get_offset(int *offset_arr, int nb)
{
	int i;

	i = 0;
	while (nb > offset_arr[i])
		i++;
	return (i);
}

static void		add_nb_lines(t_parser_graph *p_graph, t_buff_printer *buff)
{
	char	*tmp;

	add_str(buff, "\nTotal lines: ");
	if (!(tmp = ft_itoa(p_graph->nb_lines)))
	{
		p_graph->msg = "Error : malloc";
		error_sys();
	}
	add_str(buff, tmp);
	free(tmp);
	add_str(buff, "\n\n");
}

int		print_res(t_parser_graph *p_graph, t_paths *paths)
{
	int i;
	int j;
	int k;
	int *offset_arr;
	char *tmp;
	t_buff_printer	buff;

	i = 0;
	buff.index = 0;
	if (!(offset_arr = (int*)malloc(sizeof(int)
	* (paths->paths[0].ants_on + paths->paths[0].len + 1)
	* ((paths->paths[0].ants_on + paths->paths[0].len) >> 1))))
		return (set_msg(FAILURE, p_graph, "Error : malloc"));
	offset_arr[0] = INT_MAX;
	while (i < paths->paths[0].ants_on + paths->paths[0].len)
	{
		k = i + 1;
		while (k--)
		{
			j = -1;
			while (++j < paths->size)
			{
				if (k > paths->paths[j].len)
					continue ;
				else if (i - k >= paths->paths[j].ants_on)
				{
					if (k == 0)
						add_offset(offset_arr, paths->size * (i - k) + j);
					continue;
				}
				if (!(tmp = ft_itoa(paths->size * (i - k) + j + 1 - get_offset(offset_arr, paths->size * (i - k) + j))))
				{
					free(offset_arr);
					return (set_msg(FAILURE, p_graph, "Error : malloc"));
				}
				add_str(&buff, "L");
				add_str(&buff, tmp);
				free(tmp);
				add_str(&buff, "-");
				if (k == paths->paths[j].len)
					add_str(&buff, get_name(p_graph->start, p_graph->commands.t));
				else
					add_str(&buff, get_name(p_graph->start, paths->paths[j].path[k]));
				add_str(&buff, " ");
			}
//			printf("\t\t");
		}
		i++;
		if (buff.index > 0 && buff.buff[buff.index - 1] == ' ')
			buff.index--;
		add_str(&buff, "\n");
		p_graph->nb_lines += 1;
	}
	if (p_graph->flag[BONUS_N])
		add_nb_lines(p_graph, &buff);
	write(1, buff.buff, buff.index);
	free(offset_arr);
	return (SUCCESS);
//	printf("nb lines for me : %d\n", paths->paths[0].ants_on + paths->paths[0].len);
}

/*
[0][0] | [0][1] |t|								9
[1][0] | [1][1] | [1][2] | [1][3] |t|			7
[2][0] | [2][1] | [2][2] | [2][3] | [2][4] |t|	6


i - k >= paths->paths[0].ants_on

L1-[0][0] L2-[1][0] L3-[2][0]
L1-[0][1] L2-[1][1] L3-[2][1]	L4-[0][0] L5-[1][0] L6-[2][0]
L1-[0][t] L2-[1][2] L3-[2][2]	L4-[0][1] L5-[1][1] L6-[2][1]	L7-[0][0] L8-[1][0] L9-[2][0]
		  L2-[1][3] L3-[2][3]	L4-[0][t] L5-[1][2] L6-[2][2]	L7-[0][1] L8-[1][1] L9-[2][1]	L10-[0][0] L11-[1][0] L12-[2][0]
		  L2-[1][t] L3-[2][4]			  L5-[1][3] L6-[2][3]	L7-[0][t] L8-[1][2] L9-[2][2]	L10-[0][1] L11-[1][1] L12-[2][1]	L13-[0][0] L14-[1][0] L15-[2][0]
					L3-[2][t]			  L5-[1][t] L6-[2][4]			  L8-[1][3] L9-[2][3]	L10-[0][t] L11-[1][2] L12-[2][2]	L13-[0][1] L14-[1][1] L15-[2][1]	L16-[0][0] L17-[1][0] L18-[2][0]
													L6-[2][t]			  L8-[1][t] L9-[2][4]			   L11-[1][3] L12-[2][3]	L13-[0][t] L14-[1][2] L15-[2][2]	L16-[0][1] L17-[1][1] L18-[2][1]
																					L9-[2][t]			   L11-[1][t] L12-[2][4]			   L14-[1][3] L15-[2][3]	L16-[0][t] L17-[1][2] L18-[2][2]
																													  L12-[2][t]			   L14-[1][t] L15-[2][4]			   L17-[1][3] L18-[2][3]
																																						  L15-[2][t]			   L17-[1][t] L18-[2][4]
																																															  L18-[2][t]
0|1|t|			1


0|1|t|			2
0|1|2|t|		1

0|1|t|			2
0|1|t|			2
0|1|t|			2
*/
