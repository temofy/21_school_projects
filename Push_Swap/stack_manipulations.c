/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_manipulations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:07:11 by cheller           #+#    #+#             */
/*   Updated: 2019/06/25 21:07:13 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

t_stack	*stack_malloc(int amount)
{
	t_stack	*stack;

	stack = (t_stack*)ft_memalloc(sizeof(t_stack));
	stack->data = ft_memalloc(amount * sizeof(int));
	stack->size = 0;
	return (stack);
}

int		is_sorted_stack(t_stack *a, t_stack *b)
{
	int		i;

	if (!a->size)
		return (0);
	if (b->size)
		return (1);
	i = a->size - 1;
	while (i > 0)
	{
		if (a->data[i] > a->data[i - 1])
			return (1);
		i--;
	}
	return (2);
}

void	free_stack(t_stack *stack)
{
	if (!stack)
		return ;
	free(stack->data);
	free(stack);
}

int		read_arguments(t_stack *a, int amount, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (amount)
	{
		if (ft_atopi(argv[amount]) == NULL)
			return (-1);
		a->data[i] = *ft_atopi(argv[amount]);
		a->size++;
		j = -1;
		while (++j < i)
			if (a->data[j] == a->data[i])
				return (-1);
		amount--;
		i++;
	}
	return (0);
}

int		select_operation(char *operation, t_stack *a, t_stack *b)
{
	int rtn;

	rtn = -1;
	if (ft_strcmp(operation, "sa") == 0)
		rtn = swap(a);
	else if (ft_strcmp(operation, "sb") == 0)
		rtn = swap(b);
	else if (ft_strcmp(operation, "ss") == 0)
	{
		swap(a);
		rtn = swap(b);
	}
	else if (ft_strcmp(operation, "pa") == 0)
		rtn = push(a, b);
	else if (ft_strcmp(operation, "pb") == 0)
		rtn = push(b, a);
	else if (ft_strcmp(operation, "ra") == 0)
		rtn = rotate(a);
	else if (ft_strcmp(operation, "rb") == 0)
		rtn = rotate(b);
	else if (ft_strcmp(operation, "rra") == 0)
		rtn = reverse_rotate(a);
	else if (ft_strcmp(operation, "rrb") == 0)
		rtn = reverse_rotate(b);
	return (select_mul_operation(operation, a, b, rtn));
}
