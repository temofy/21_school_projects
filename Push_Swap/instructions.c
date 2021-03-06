/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:09:44 by cheller           #+#    #+#             */
/*   Updated: 2019/06/25 21:09:46 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		swap(t_stack *stack)
{
	int tmp;

	if (stack->size < 2)
		return (0);
	tmp = stack->data[stack->size - 1];
	stack->data[stack->size - 1] = stack->data[stack->size - 2];
	stack->data[stack->size - 2] = tmp;
	return (1);
}

int		push(t_stack *in, t_stack *out)
{
	if (out->size != 0)
	{
		out->size--;
		in->data[in->size] = out->data[out->size];
		in->size++;
	}
	return (1);
}

int		rotate(t_stack *stack)
{
	int i;
	int tmp;

	i = 0;
	if (stack->size < 2)
		return (0);
	tmp = stack->data[i + 1];
	while (i < stack->size - 2)
	{
		stack->data[i + 1] = stack->data[0];
		stack->data[0] = tmp;
		tmp = stack->data[i + 2];
		i++;
	}
	stack->data[i + 1] = stack->data[0];
	stack->data[0] = tmp;
	return (1);
}

int		reverse_rotate(t_stack *stack)
{
	int i;
	int tmp;

	i = stack->size - 1;
	if (stack->size < 1)
		return (0);
	tmp = stack->data[i - 1];
	while (i > 0)
	{
		stack->data[i - 1] = stack->data[stack->size - 1];
		stack->data[stack->size - 1] = tmp;
		if (i > 1)
			tmp = stack->data[i - 2];
		i--;
	}
	return (1);
}

int		select_mul_operation(char *operation, t_stack *a, t_stack *b, int rtn)
{
	if (ft_strcmp(operation, "rr") == 0)
	{
		rotate(a);
		rtn = rotate(b);
	}
	else if (ft_strcmp(operation, "rrr") == 0)
	{
		reverse_rotate(a);
		rtn = reverse_rotate(b);
	}
	else if (rtn == -1)
	{
		free(operation);
		return (-1);
	}
	free(operation);
	return (rtn);
}
