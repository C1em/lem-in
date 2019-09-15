/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <cbenoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:29:22 by cbenoit           #+#    #+#             */
/*   Updated: 2019/09/15 12:19:38 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include <stdlib.h>

static int	*setup_zero(int *to_init, size_t size, int value)
{
	size_t		i;

	i = 0;
	while (i < size)
		to_init[i++] = value;
	return (to_init);
}

static int	fill_flag(t_parser_graph *graph, int caracter)
{
	if (caracter == 'c')
		graph->flag[BONUS_C] = 1;
	else if (caracter == 'v')
		graph->flag[BONUS_V] = 1;
	else if (caracter == 'n')
		graph->flag[BONUS_N] = 1;
	else if (caracter == 'p')
		graph->flag[BONUS_P] = 1;
	else if (caracter == 'd')
		graph->flag[BONUS_D] = 1;
	else if (caracter == 'm')
		graph->flag[BONUS_M] = 1;
	else
		return (FAILURE);
	return (SUCCESS);
}

int			fill_option(t_parser_graph *graph, char **av)
{
	int		i;
	int		j;

	setup_zero(graph->flag, 6, 0);
	i = 0;
	while (++i < 4 && av[i])
	{
		if (av[i][0] == '-')
		{
			j = 0;
			while (av[i][++j])
				if (fill_flag(graph, av[i][j]) == FAILURE)
					return (FAILURE);
		}
		else
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	print_ants_at_ends(t_parser_graph *p_graph, t_buff_printer *buff)
{
	char	*tmp;

	if (!(tmp = ft_itoa(p_graph->ants_at_end)))
		return (FAILURE);
	add_str(buff, tmp);
	free(tmp);
}

int			print_ants_state(t_parser_graph *p_graph, t_buff_printer *buff)
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
	print_ants_next(p_graph, buff);
	add_str(buff, "\n");
	return (SUCCESS);
}
