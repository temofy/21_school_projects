/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:13:39 by cheller           #+#    #+#             */
/*   Updated: 2019/06/28 14:13:41 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(t_stack *stack, char name_stack)
{
	if (name_stack == 'a')
	{
		swap(stack);
		write(1, "sa\n", 3);
	}
	else if (name_stack == 'b')
	{
		swap(stack);
		write(1, "sb\n", 3);
	}
}

void	ft_push(t_stack *in, t_stack *out, char name_in)
{
	if (name_in == 'a')
	{
		push(in, out);
		write(1, "pa\n", 3);
	}
	else if (name_in == 'b')
	{
		push(in, out);
		write(1, "pb\n", 3);
	}
}

void	ft_rotate(t_stack *stack, char name_stack)
{
	if (name_stack == 'a')
	{
		rotate(stack);
		write(1, "ra\n", 3);
	}
	else if (name_stack == 'b')
	{
		rotate(stack);
		write(1, "rb\n", 3);
	}
}

void	ft_reverse_rotate(t_stack *stack, char name_stack)
{
	if (name_stack == 'a')
	{
		reverse_rotate(stack);
		write(1, "rra\n", 4);
	}
	else if (name_stack == 'b')
	{
		reverse_rotate(stack);
		write(1, "rrb\n", 4);
	}
}

void	rotate_n_order(t_stack *stack)
{
	int	min;
	int	min_value;

	min = find_min_el(stack);
	min_value = stack->data[min];
	while (stack->data[stack->size - 1] != min_value)
	{
		if (min > stack->size / 2)
			ft_rotate(stack, 'a');
		else
			ft_reverse_rotate(stack, 'a');
	}
}
