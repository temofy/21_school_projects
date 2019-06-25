/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_steps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:25:38 by cheller           #+#    #+#             */
/*   Updated: 2019/06/25 20:31:15 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		count_steps_i(t_stack *a, int index)
{
	int	steps;

	if (!ft_iseven(a->size))
	{
		if (index >= a->size / 2)
			steps = a->size / 2 - ft_abs(a->size / 2 - index);
		else
			steps = (a->size / 2 - (a->size / 2 - index) + 1);
	}
	else
	{
		if (index >= a->size / 2)
			steps = (a->size / 2 - ft_abs(a->size / 2 - index)) - 1;
		else
			steps = (a->size / 2 - (a->size / 2 - index) + 1);
	}
	return (steps);
}

void	steps_to_a(t_stack *a, int val, t_steps *steps, t_first_loc *seq)
{
	int	i;
	int min;

	steps[0].a_steps = 0;
	i = a->size;
	if (a->data[a->size - 1] > val && val > find_boundaries(seq, a->data[i - 1]))
	{
		steps[0].a_index = find_place(a, val);
		steps[0].a_steps = count_steps_i(a, steps[0].a_index);
		return ;
	}
	while (--i >= 0)
	{
		steps[0].a_steps = count_steps_i(a, i);
		if (a->data[i] > val && val > find_boundaries(seq, a->data[i]))
		{
			steps[0].a_index = i;
			return ;
		}
	}
	if (a->data[0] < val && val > find_boundaries(seq, a->data[0]))
	{
		min = find_min_el(a);
		steps[0].a_index = min;
		steps[0].a_steps = count_steps_i(a, steps[0].a_index);
		return ;
	}
}

int		analyze_steps(t_steps *steps, int size)
{
	int i;
	int min;
	int index;

	i = 0;
	min = steps[0].total;
	index = 0;
	while (++i < size)
	{
		if (min > steps[i].total)
		{
			min = steps[i].total;
			index = i;
		}
	}
	return (index);
}
