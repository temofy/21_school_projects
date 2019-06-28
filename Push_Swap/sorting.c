/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 13:59:01 by cheller           #+#    #+#             */
/*   Updated: 2019/06/28 13:59:04 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_steps		*analyze_stacks(t_stack *a, t_stack *b, t_first_loc *seq)
{
	t_steps		*steps;
	int			i;

	steps = (t_steps*)malloc(sizeof(t_steps) * b->size);
	i = b->size;
	while (--i >= 0)
	{
		steps[i].b_steps = count_steps_i(b, i);
		steps_to_a(a, b->data[i], steps + i, seq);
		steps[i].b_index = i;
		steps[i].total = steps[i].a_steps + steps[i].b_steps;
	}
	return (steps);
}

void		rotation_a(t_stack *a, t_steps *steps, int index)
{
	while (steps[index].a_index < a->size - 1)
	{
		if (steps[index].a_index >= a->size / 2)
		{
			ft_rotate(a, 'a');
			steps[index].a_index++;
		}
		else
		{
			ft_reverse_rotate(a, 'a');
			steps[index].a_index--;
			steps[index].a_index = (steps[index].a_index < 0)
					? a->size - 1 : steps[index].a_index--;
		}
	}
}

void		pull_el(t_stack *a, t_stack *b, int index, t_steps *steps)
{
	while (steps[index].b_index < b->size - 1)
	{
		if (steps[index].b_index >= b->size / 2)
		{
			ft_rotate(b, 'b');
			steps[index].b_index++;
		}
		else
		{
			ft_reverse_rotate(b, 'b');
			steps[index].b_index--;
			steps[index].b_index = (steps[index].b_index < 0)
					? b->size - 1 : steps[index].b_index--;
		}
	}
	rotation_a(a, steps, index);
	ft_push(a, b, 'a');
}

void		throw_to_b(t_stack *a, t_stack *b)
{
	int	i;

	i = a->size;
	while (--i > 2)
	{
		push(b, a);
		write(1, "pb\n", 3);
	}
}

void		throw_except(t_stack *a, t_stack *b, t_seq *sorted_seq)
{
	int	i;
	int k;

	i = a->size;
	while (--i >= 0)
	{
		if (i > sorted_seq->start)
			ft_push(b, a, 'b');
		if (i == sorted_seq->start && i != sorted_seq->amount - 1)
		{
			k = sorted_seq->amount;
			while (k-- > 0)
				ft_rotate(a, 'a');
			sorted_seq->start = sorted_seq->amount - 1;
			sorted_seq->end = 0;
			i++;
		}
		if (i == 0 && a->size != sorted_seq->amount)
			i = a->size;
	}
}
