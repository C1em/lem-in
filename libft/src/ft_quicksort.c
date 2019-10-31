/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:31:18 by coremart          #+#    #+#             */
/*   Updated: 2019/10/31 23:34:26 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_swap(int *restrict const a, int *restrict const b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition(int arr[], int low, int high)
{
	int	swapable;

	swapable = low;
	while (low < high)
	{
		if (arr[low] < arr[high])
			ft_swap(&arr[low], &arr[swapable++]);
		low++;
	}
	ft_swap(&arr[low], &arr[swapable]);
	return (swapable);
}

void		ft_qsort(int arr[], int low, int high)
{
	int	pivot_index;

	if (low >= high)
		return ;
	pivot_index = partition(arr, low, high);
	ft_qsort(arr, low, pivot_index - 1);
	ft_qsort(arr, pivot_index + 1, high);
}

void		ft_quicksort(int *arr, int size)
{
	ft_qsort(arr, 0, size - 1);
}
