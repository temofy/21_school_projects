/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:42:53 by cheller           #+#    #+#             */
/*   Updated: 2019/06/26 12:55:04 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	first_sort(t_stack *a)
{
	int min;

	min = find_min_el(a);
	if (a->data[2] > a->data[1] && a->data[0] > a->data[2])
		ft_swap(a, 'a');
	else if (a->data[2] > a->data[1] && a->data[0] < a->data[2])
		ft_rotate(a, 'a');
	if (a->data[2] > a->data[1])
		ft_swap(a, 'a');
	if (a->data[1] > a->data[0] && a->data[2] < a->data[1] && 2 == min)
	{
		ft_reverse_rotate(a, 'a');
		ft_swap(a, 'a');
	}
	else if (a->data[1] > a->data[0])
		ft_reverse_rotate(a, 'a');
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
	if (a->size > 2 && is_sorted_stack(a, b) != 2)
	{
		sorted_seq = find_sorted_seq(a);
		if (sorted_seq->amount > 2)
			throw_except(a, b, sorted_seq);
		if (sorted_seq->amount < 3 && a->size != 3)
		{
			throw_to_b(a, b);
			first_sort(a);
		}
		else
			first_sort(a);
		sort_stack(a, b);
		rotate_n_order(a);
		free(sorted_seq);
	}
	if (a->size == 2 && is_sorted_stack(a, b) == 1)
		ft_swap(a, 'a');
}

int		push_swap(int amount, char *argv[])
{
	t_stack		*a;
	t_stack		*b;
	int			rtn;

	a = stack_malloc(amount);
	b = stack_malloc(amount);
	rtn = read_arguments(a, amount, &*argv);
	if (a->size > 0 && rtn != -1)
	{
		initialize_start(a, b);
		rtn = is_sorted_stack(a, b);
	}
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
		ft_arrdel(&instructions);
	}
	else
		rtn = push_swap(argc - 1, &*argv);
	if (rtn == -1)
		write(2, "Error\n", 6);
	return (rtn);
}
