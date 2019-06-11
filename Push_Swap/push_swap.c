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
#include <stdio.h>

typedef struct	s_sorted_sequence
{
	int			min;
	int 		i_min;
	int			max;
	int 		i_max;
	int 		amount_ordered;
}				t_sorted_seq;

typedef struct	s_boundary_values
{
	int			min;
	int			max;
	int 		middle;
}				t_boundaries;

t_sorted_seq	analyze_sorted_seq(t_stack *a)
{
	t_sorted_seq	seq;
	t_sorted_seq	tmp;
	int 			i;
	int 			j;
	int 			counter;

	seq.amount_ordered = 0;
	seq.min = a->data[a->size - 1];
	seq.i_min = a->size - 1;
	seq.max = a->data[a->size - 1];
	seq.i_max = a->size - 1;
	if (a->size > 2)
		i = a->size - 1;
	else
	{
		//при двух элементах или одном элементе
	}
	while (i >= 0)
	{
		j = i;
		tmp.min = a->data[i];
		tmp.i_min = i;
		tmp.max = a->data[i];
		tmp.i_max = i;
		counter = 1;
		while (--j >= 0)
		{
			if (a->data[j] > tmp.max)
			{
				tmp.max = a->data[j];
				tmp.i_max = j;
				counter++;
			}
			else
				break;
		}
		if (counter > seq.amount_ordered)
		{
			seq.max = tmp.max;
			seq.i_max = tmp.i_max;
			seq.min = tmp.min;
			seq.i_min = tmp.i_min;
			seq.amount_ordered = counter;
		}
		i -= counter;
	}
	//printf("min index: %d\nmin: %d\nmax index: %d\nmax: %d\namount: %d\n", seq.i_min, seq.min, seq.i_max, seq.max, seq.amount_ordered);
	return (seq);
}

t_boundaries	analyze_boundaries(t_stack *stack)
{
	t_boundaries	boundaries;
	int 			i;

	i = stack->size - 1;
	boundaries.max = stack->data[stack->size - 1];
	boundaries.min = stack->data[stack->size - 1];
	while (--i >= 0)
	{
		if (stack->data[i] > boundaries.max)
			boundaries.max = stack->data[i];
		if (stack->data[i] < boundaries.min)
			boundaries.min = stack->data[i];
	}
	boundaries.middle = (boundaries.max + boundaries.min) / 2;

	i = stack->size - 1;
	while (--i >= 0)
	{

	}
	return (boundaries);
}

t_sorted_seq	first_cleansing(t_stack *a, t_stack *b, t_sorted_seq seq)
{

}
void	initialize_start(t_stack *a, t_stack *b)
{
	t_sorted_seq	seq;
	t_boundaries	boundaries;
	int 			i;
	int 			j;

	i = a->size;
	boundaries = analyze_boundaries(a);
	printf("min: %d\nmax: %d\nmiddle: %d\n", boundaries.min, boundaries.max, boundaries.middle);
	while(--i >= 2)
	{
		if (a->data[i] != boundaries.min && a->data[i] != boundaries.middle)
		{
			push(b, a);
			write(1, "pb\n", 3);
		}
		else
		{
			rotate(a);
			write(1, "ra\n", 3);
			i++;
		}
	}

	//seq = analyze_sorted_seq(a);
	//printf("min index: %d\nmin: %d\nmax index: %d\nmax: %d\namount: %d\n", seq.i_min, seq.min, seq.i_max, seq.max, seq.amount_ordered);
}

int 	push_swap(int amount, char *argv[])
{
	t_stack		*a;
	t_stack		*b;
	int 		rtn;

	a = stack_malloc(amount);
	b = stack_malloc(amount);
	if ((rtn = read_arguments(a, amount, &*argv)) == -1)
		return (rtn);
	initialize_start(a, b);
	rtn = is_sorted_stack(a, b);
	print_stack(a, b);
	free_stack(a);
	free_stack(b);
	return (rtn);
}

int 	main(int argc, char *argv[])
{
	int 	rtn;
	char 	**instructions;

	if (argc == 1)
		return (0);
	if (argc == 2)
	{
		instructions = ft_strsplit(argv[1], ' ');
		rtn = push_swap(5, instructions - 1);
	}
	else
		rtn = push_swap(argc - 1, &*argv);
	if (rtn == -1)
		write(2, "Error\n", 6);
	if (rtn == 1)
		write(1, "KO\n", 3);
	if (rtn == 2)
		write(1, "OK\n", 3);
	return (rtn);
}