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

typedef struct	s_the_nearests
{
	int			max[3];
	int 		max_to_median[3];
}				t_the_nearests;

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

t_boundaries	 analyze_boundaries(t_stack *stack)
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

int 	find_min_el(t_stack *stack)
{
	int min;
	int i;
	int index;

	i = 0;
	index = 0;
	min = stack->data[0];
	while (++i < stack->size)
	{
		if (min > stack->data[i])
		{
			index = i;
			min = stack->data[i];
		}
	}
	return (index);
}

int 	find_max_el(t_stack *stack)
{
	int max;
	int i;
	int index;

	i = 0;
	index = 0;
	max = stack->data[0];
	while (++i < stack->size)
	{
		if (max < stack->data[i])
		{
			index = i;
			max = stack->data[i];
		}
	}
	return (index);
}

void	pulling_needful_el(t_stack *stack, int index)
{

}

void	count_steps(t_stack *stack, t_the_nearests *nearests)
{
	/*if (ft_iseven(stack->size))
	{*/
		if (nearests->max_to_median[1] < stack->size / 2 || nearests->max[1] < stack->size / 2)
		{
			if (nearests->max_to_median[1] < nearests->max[1])
			{
				nearests->max_to_median[2] = nearests->max_to_median[1];
				nearests->max_to_median[2] += 1;
			}
			else
			{
				nearests->max[2] = nearests->max[1];
				nearests->max[2] += 1;
			}
		}
		if (nearests->max_to_median[1] >= stack->size / 2 || nearests->max[1] >= stack->size / 2)
		{
			if (nearests->max_to_median[1] > nearests->max[1])
			{
				nearests->max_to_median[2] = stack->size - 1;
				nearests->max_to_median[2] -= nearests->max_to_median[1];
			}
			else
			{
				nearests->max[2] = stack->size - 1;
				nearests->max[2] -= nearests->max[1];
			}
		}
}

t_the_nearests	analyze_the_nearest(t_stack *stack, int median)
{
	t_the_nearests	the_nearests;
	int 			i;

	the_nearests.max[1] = find_max_el(stack);
	the_nearests.max[0] = stack->data[the_nearests.max[1]];

	the_nearests.max_to_median[1] = find_min_el(stack);
	the_nearests.max_to_median[0] = stack->data[the_nearests.max_to_median[1]];
	i = -1;
	while (++i < stack->size)
	{
		if (stack->data[i] > the_nearests.max_to_median[0] && stack->data[i] < median)
		{
			the_nearests.max_to_median[0] = stack->data[i];
			the_nearests.max_to_median[1] = i;
		}
	}
	count_steps(stack, &the_nearests);
	return (the_nearests);
}

void	put_min_or_max_el(t_stack *stack)
{
	int	min;
	int max;
	int i;
	int remoteness;
	int start;
	int end;
	int steps = 0;

	end = 0;
	start = 0;
	i = stack->size - 1;
	min = find_min_el(stack);
	max = find_max_el(stack);
	printf("min: %i\nmax: %i\n", min, max);
	remoteness = 0;
	//while (i > -1)
	//{
		if (i == min || i == max)
			return ;
		else
		{
			if (ft_iseven(stack->size))
			{
				if (min < stack->size / 2 || max < stack->size / 2)
				{
					steps += (min < max) ? min : max;
					steps += 1;
					if (min < max)
						printf("Это минимальное число\n");
					else
						printf("Это максимальное число\n");
					printf("Шагов: %i\n", steps);
				}
				if (min >= stack->size / 2 || max >= stack->size / 2)
				{
					steps = stack->size - 1;
					steps -= (min > max) ? min : max;
					if (min > max)
						printf("Это минимальное число\n");
					else
						printf("Это максимальное число\n");
					printf("Шагов: %i\n", steps);
				}
			}
			/*while (remoteness != (stack->size) / 2)
			{
				remoteness++;
				if (stack->data[remoteness - 1] == min || stack->data[remoteness - 1 ] == max)
				{

				}
				if (stack->data[i - remoteness] == min || stack->data[i - remoteness] == max)
				{

				}
			}*/
		}
	//}
}

void	pulling_out(t_stack *a, t_stack *b, int	index)
{
	int i;

	i = -1;
	if (index < (b->size / 2))
	{
		while (++i <= index)
		{
			reverse_rotate(b);
			write(1, "rrb\n", 4);
		}
	}
	else
	{
		// проанализировать следующие элеменеты
		while (++i < b->size - index - 1)
		{
			rotate(b);
			write(1, "rb\n", 3);
		}
	}
	push(a, b);
	write(1, "pa\n", 3);
}

void	shift_up(t_stack *a, t_stack *b, t_the_nearests nearests, t_boundaries boundaries)
{
	char 	*shortest;

	shortest = (nearests.max[2] < nearests.max_to_median[2]) ? "max" : "max_to_m";
	printf("Way %s\n", shortest);
	if (a->data[a->size - 1] == boundaries.max)
	{
		if (ft_strcmp("max", shortest) == 0)
		{
			pulling_out(a, b, nearests.max[1]);
		}
		else
		{
			rotate(a);
			write(1, "ra\n", 3);
			if (a->data[a->size - 1] == boundaries.middle)
			{
				swap(a);
				write(1, "sa\n", 3);
			}
			//if ((nearests.max_to_median[2] - nearests.max[2]) > 0) // исправить
			//{
			pulling_out(a, b, nearests.max_to_median[1]);
			// можно начать анализировать следующие позиции в b для совместного swap
			swap(a);
			write(1, "sa\n", 3);
			//}
			// анализируем и сортируем а
		}
	}
	else
	{
		if (a->data[a->size - 1] == boundaries.middle && a->data[a->size - 2] == boundaries.min)
		{
			swap(a);
			write(1, "sa\n", 3);
		}
		/*else
		{
			reverse_rotate(a);
			write(1, "rra\n", 4);
		}*/
	}
}
/*void	sort_stack(t_stack *a, t_stack *b, t_boundaries boundaries)
{
	t_the_nearests nearests;

	while (!(is_sorted_stack(a, b)))
	{

	}
	nearests = analyze_the_nearest(b, boundaries.middle);
	printf("max:%i\nMax steps: %i\nmax_to_m: %i\n", nearests.max[0], nearests.max[2], nearests.max_to_median[0]);
	printf("Max_to_median steps: %i\n", nearests.max_to_median[2]);
	shift_up(a, b, nearests, boundaries);
}

void	initialize_start(t_stack *a, t_stack *b)
{
	t_sorted_seq	seq;
	t_boundaries	boundaries;
	int 			i;

	i = a->size;
	boundaries = analyze_boundaries(a);
	printf("min: %d\nmax: %d\nmiddle: %d\n", boundaries.min, boundaries.max, boundaries.middle);
	while(--i >= 3)
	{
		if (a->data[i] != boundaries.min && a->data[i] != boundaries.middle
			&& a->data[i] != boundaries.max)
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
	sort_stack(a, b, boundaries);*/

	//put_min_or_max_el(b);
	/*if(a->data[1] == boundaries.middle)
	{
		swap(a);
		write(1, "sa\n", 3);
	}*/

	//seq = analyze_sorted_seq(a);
	//printf("min index: %d\nmin: %d\nmax index: %d\nmax: %d\namount: %d\n", seq.i_min, seq.min, seq.i_max, seq.max, seq.amount_ordered);
//}

int 	push_swap(int amount, char *argv[])
{
	t_stack		*a;
	t_stack		*b;
	int 		rtn;

	a = stack_malloc(amount);
	b = stack_malloc(amount);
	if ((rtn = read_arguments(a, amount, &*argv)) == -1)
		return (rtn);
	print_stack(a, b);
	initialize_start(a, b);
	rtn = is_sorted_stack(a, b);
	//print_stack(a, b);
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
		rtn = push_swap(ft_arraylen(instructions), instructions - 1);
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