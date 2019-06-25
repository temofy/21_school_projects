/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:42:53 by cheller           #+#    #+#             */
/*   Updated: 2019/06/05 13:43:15 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	first_sort(t_stack *stack)
{
	if (stack->data[2] > stack->data[1] && stack->data[0] > stack->data[2])
	{
		swap(stack);
		write(1, "sa\n", 3);
	}
	else if (stack->data[2] > stack->data[1] && stack->data[0] < stack->data[2])
	{
		rotate(stack);
		write(1, "ra\n", 3);
	}
	if (stack->data[2] > stack->data[1])
	{
		swap(stack);
		write(1, "sa\n", 3);
	}
	if (stack->data[1] > stack->data[0])
	{
		reverse_rotate(stack);
		write(1, "rra\n", 4);
		swap(stack);
		write(1, "sa\n", 3);
	}
}

void	sort_stack(t_stack *a, t_stack *b)
{
	t_steps		*steps;
	int			index;
	t_first_loc	seq;

	seq.min = a->data[2];
	seq.middle = a->data[1];
	seq.max = a->data[0];
	while (b->size)
	{
		steps = analyze_stacks(a, b, &seq);
		index = analyze_steps(steps, b->size);
		pull_el(a, b, index, steps);
		seq.min = a->data[find_min_el(a)];
		seq.max = a->data[find_max_el(a)];
		free(steps);
	}
}

void	initialize_start(t_stack *a, t_stack *b)
{
	t_seq	*sorted_seq;

	if (a->size < 2 && b->size > 0)
		return ;
	sorted_seq = find_sorted_seq(a);
	if (sorted_seq->amount > 2)
		throw_except(a, b, sorted_seq);
	if (sorted_seq->amount < 3)
	{
		throw_to_b(a, b);
		first_sort(a);
	}
	sort_stack(a, b);
	rotate_n_order(a);
	free(sorted_seq);
}

int		push_swap(int amount, char *argv[])
{
	t_stack		*a;
	t_stack		*b;
	int			rtn;

	a = stack_malloc(amount);
	b = stack_malloc(amount);
	if ((rtn = read_arguments(a, amount, &*argv)) == -1)
		return (rtn);
	initialize_start(a, b);
	rtn = is_sorted_stack(a, b);
	free_stack(a);
	free_stack(b);
	return (rtn);
}

int		main(int argc, char *argv[])
{
	int		rtn;
	char	**instructions;

	if (argc == 1)
		return (0);
	if (argc == 2)
	{
		instructions = ft_strsplit(argv[1], ' ');
		rtn = push_swap(ft_arraylen((void**)instructions), instructions - 1);
	}
	else
		rtn = push_swap(argc - 1, &*argv);
	return (rtn);
}
