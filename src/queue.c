/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:34:35 by coremart          #+#    #+#             */
/*   Updated: 2019/09/15 06:54:58 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
#include <stdlib.h>

int		init_queue(t_queue_ptr *queue, int vertex)
{
	t_queue *queue_elem;

	if (!(queue_elem = (t_queue*)malloc(sizeof(t_queue))))
		return (FAILURE);
	queue->start = queue_elem;
	queue->end = queue_elem;
	queue_elem->value = vertex;
	queue_elem->next = NULL;
	return (SUCCESS);
}

int		enqueue(t_queue_ptr *queue, int vertex)
{
	t_queue *queue_elem;

	if (!(queue_elem = (t_queue*)malloc(sizeof(t_queue))))
		return (FAILURE);
	if (queue->start == NULL)
		queue->start = queue_elem;
	else
		queue->end->next = queue_elem;
	queue_elem->value = vertex;
	queue_elem->next = NULL;
	queue->end = queue_elem;
	return (SUCCESS);
}

int		dequeue(t_queue_ptr *queue)
{
	int		value;
	t_queue	*tmp;

	value = queue->start->value;
	tmp = queue->start;
	queue->start = queue->start->next;
	free(tmp);
	return (value);
}

void	free_queue(t_queue_ptr *queue)
{
	t_queue	*tmp;

	while (queue->start != NULL)
	{
		tmp = queue->start;
		queue->start = queue->start->next;
		free(tmp);
	}
}
