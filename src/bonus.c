/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:29:22 by cbenoit           #+#    #+#             */
/*   Updated: 2019/09/15 11:58:12 by coremart         ###   ########.fr       */
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
	if (!(tmp = ft_itoa(p_graph->ants_at_end)))
		return (FAILURE);
	add_str(buff, tmp);
	free(tmp);
	add_str(buff, "\n");
	return (SUCCESS);
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
