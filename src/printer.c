/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 02:16:35 by coremart          #+#    #+#             */
/*   Updated: 2019/09/09 06:24:04 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <limits.h>
#include <stdlib.h>

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

void	print_res(t_parser_graph *p_graph, t_paths *paths)
{
	int i;
	int j;
	int k;
	int *offset_arr;

// i = position in path && nb of ants on path
// k = counter that go from 0 to i at each
// j = path nb

	i = 0;
	if (!(offset_arr = (int*)malloc(sizeof(int) * p_graph->ants)))
		exit(1);
	offset_arr[0] = INT_MAX;
	while (i < paths->paths[0].ants_on + paths->paths[0].len) // 2
	{
		k = i + 1;
		while (k--) //
		{
			j = -1;
			while (++j < paths->size)
			{
				if (k > paths->paths[j].len)
				{
					printf("\t\t");
					continue ;
				}
				else if (i - k >= paths->paths[j].ants_on)
				{
					if (k == 0)
						add_offset(offset_arr, paths->size * (i - k) + j);
					continue;
				}
				if (k == paths->paths[j].len)
					printf("L%2d-%s\t", paths->size * (i - k) + j + 1 - get_offset(offset_arr, paths->size * (i - k) + j), get_name(p_graph->start, p_graph->commands.t));
				else
					printf("L%2d-%s", paths->size * (i - k) + j + 1 - get_offset(offset_arr, paths->size * (i - k) + j), get_name(p_graph->start, paths->paths[j].path[k]));
				if (j < paths->size)
					printf("\t");
			}
			printf("\t\t");
		}
		i++;
		printf("\n");
	}
	free(offset_arr);
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
