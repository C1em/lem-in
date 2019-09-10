/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:34:35 by coremart          #+#    #+#             */
/*   Updated: 2019/09/10 16:35:58 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include <stdlib.h>

void			init_queue(t_queue_ptr *queue, int vertex)
{
	t_queue *queue_elem;

	if (!(queue_elem = (t_queue*)malloc(sizeof(t_queue))))
		exit(1);
	queue->start = queue_elem;
	queue->end = queue_elem;
	queue_elem->value = vertex;
	queue_elem->next = NULL;
}

void			enqueue(t_queue_ptr *queue, int vertex)
{
	t_queue *queue_elem;

	if (!(queue_elem = (t_queue*)malloc(sizeof(t_queue))))
		exit(1);
	if (queue->start == NULL)
		queue->start = queue_elem;
	else
		queue->end->next = queue_elem;
	queue_elem->value = vertex;
	queue_elem->next = NULL;
	queue->end = queue_elem;
}

int				dequeue(t_queue_ptr *queue)
{
	int	value;
	t_queue			*tmp;

	value = queue->start->value;
	tmp = queue->start;
	queue->start = queue->start->next;
	free(tmp);
	return (value);
}

void			free_queue(t_queue_ptr *queue)
{
	t_queue	*tmp;

	while (queue->start != NULL)
	{
		tmp = queue->start;
		queue->start = queue->start->next;
		free(tmp);
	}
}
