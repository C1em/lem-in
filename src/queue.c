/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:34:35 by coremart          #+#    #+#             */
/*   Updated: 2019/06/25 19:26:19 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include <stdlib.h>

void	init_queue(t_queue_ptr *queue)
{
	queue->start = NULL;
	queue->size = 0;
}

void	enqueue(t_queue_ptr *queue, int vertex)
{
	t_queue *queue_elem;

	if (!(queue_elem = (t_queue*)malloc(sizeof(t_queue))))
		exit(1);
	if (queue->size == 0)
		queue->start = queue_elem;
	else
		queue->end->next = queue_elem;
	queue_elem->value = vertex;
	queue_elem->next = NULL;
	queue->end = queue_elem;
	++queue->size;
}

t_queue	*dequeue(t_queue_ptr *queue)
{
	t_queue	*queue_elem;

	if (queue->size == 0)
		return NULL;
	queue_elem = queue->start;
	queue->start = queue_elem->next;
	--queue->size;
	return (queue_elem);
}

void	free_queue(t_queue_ptr *queue)
{
	t_queue *queue_elem;

	while ((queue_elem = dequeue(queue)) != NULL)
		free(queue_elem);
}
