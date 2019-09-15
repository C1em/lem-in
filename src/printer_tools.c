/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:46:06 by cbenoit           #+#    #+#             */
/*   Updated: 2019/09/15 12:24:04 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

void		add_str(t_buff_printer *buff, char *str)
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

char		*get_name(t_vertex_list *list, int vertex)
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

int			add_nb_lines(t_parser_graph *p_graph, t_buff_printer *buff)
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
