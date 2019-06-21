#include "push_swap.h"

typedef struct s_sorted_seq
{
	int		start;
	int 	end;
	int 	amount;
}				t_seq;

typedef struct	s_steps
{
	int		a_steps;
	int 	a_index;
	int 	b_steps;
	int 	b_index;
	int 	total;
}				t_steps;

typedef struct	s_first_location
{
	int 	min;
	int		middle;
	int 	max;
}				t_first_loc;

t_seq	*initialize_seq()
{
	t_seq	*seq;

	seq = (t_seq*)malloc(sizeof(t_seq));
	seq->amount = 0;
	seq->start = -1;
	seq->end = -1;
	return (seq);
}

t_seq	*find_sorted_seq(t_stack *stack)
{
	int		i;
	t_seq	*start_end;
	t_seq	*tmp;

	start_end = initialize_seq();
	tmp = initialize_seq();

	i = stack->size;
	while (--i > 0)
	{
		if (stack->data[i] < stack->data[i - 1])
		{
			if (tmp->start == -1)
				tmp->start = i;
		}
		else
		{
			tmp->end = i;
			tmp->amount = tmp->start - (tmp->end - 1);
			if (tmp->amount >= start_end->amount)
			{
				start_end->amount = tmp->amount;
				start_end->start = tmp->start;
				start_end->end = tmp->end;
				tmp->amount = 0;
				tmp->start = -1;
				tmp->end = -1;
			}
		}
	}
	free(tmp);
	return (start_end);
}

int		find_boundaries(t_first_loc *seq, int cur_val)
{
	if (cur_val > seq->max)
		return (seq->max);
	if (cur_val > seq->middle)
		return (seq->middle);
	if (cur_val > seq->min)
		return (seq->min);
	else
		return (-2147483648);
}

int 	count_steps_i(t_stack *a, int index)
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

int		find_place(t_stack *stack, int value)
{
	int	index;
	int i;

	index = stack->size - 1;
	if (stack->data[index])
	while (index > 0)
	{
		if (stack->data[index] < value && stack->data[index - 1] > value)
		{

		}
		index--;
	}
	if ()
	return (index);
}

void	steps_to_a(t_stack *a, int value, t_steps *steps, int index, t_first_loc *seq)
{
	int	i;

	steps[index].a_steps = 0;
	i = a->size;
	if (a->data[a->size - 1] > value && value > find_boundaries(seq, a->data[i - 1])) // проверить ситуацию
	{
		find_place(a, value);
		steps[index].a_steps = 0;
		steps[index].a_index = a->size - 1;
		return ;
	}
	while (--i >= 0)
	{
		/*if (i >= a->size / 2)
		{
			steps[index].a_steps++;
		}
		else
		{
			if (!ft_iseven(a->size) && i == (a->size / 2) - 1)
				steps[index].a_steps--;
			else if (ft_iseven(a->size) && i == (a->size / 2) - 1)
				steps[index].a_steps++;
			steps[index].a_steps--;
		}*/
		steps[index].a_steps = count_steps_i(a, i);
		if(a->data[i] > value && value > find_boundaries(seq, a->data[i]))
		{
			steps[index].a_steps;
			steps[index].a_index = i;
			return ;
		}
	}
	if (a->data[0] < value && value > find_boundaries(seq, a->data[0]))
	{
		int		min;

		min = find_min_el(a);
		steps[index].a_index = (min - 1 < 0) ? a->size - 1 : min;
		steps[index].a_steps = count_steps_i(a, steps[index].a_index);
		//steps[index].a_index = 0;
		return ;
	}
}

t_steps	 	*analyze_stacks(t_stack *a, t_stack *b, t_first_loc *seq)
{
	t_steps	*steps;
	int i;
	int instrs;

	steps = (t_steps*)malloc(sizeof(t_steps) * b->size);
	i = b->size;
	instrs = -1;
	while (--i >= 0)
	{
		/*if (i >= b->size / 2)
		{
			steps[i].b_steps = ++instrs;
		}
		else
		{
			if (!ft_iseven(b->size) && i == (b->size / 2) - 1)
				steps[i].b_steps = instrs--;
			else if (ft_iseven(b->size) && i == (b->size / 2) - 1)
				instrs++;
			steps[i].b_steps = instrs--;
		}*/
		steps[i].b_steps = count_steps_i(b, i);
		steps_to_a(a, b->data[i], steps, i, seq);
		steps[i].b_index = i;
		steps[i].total = steps[i].a_steps + steps[i].b_steps;
	}
	return (steps);
}

/*int 	steps_to_a(t_stack *a, int value)
/*int 	steps_to_a(t_stack *a, int value)
{
	int	i;
	int steps;

	steps = 0;
	i = a->size;
	if (a->data[a->size - 1] > value)
		return (0);
	while (--i >= 0)
	{
		if (i >= a->size / 2)
		{
			steps++;
		}
		else
		{
			if (!ft_iseven(a->size) && i == (a->size / 2) - 1)
				steps--;
			else if (ft_iseven(a->size) && i == (a->size / 2) - 1)
				steps++;
			steps--;
		}
		if(a->data[i] < value)
			return (steps++);
	}
	if (a->data[0] < value)
		steps = 1;
	return (steps);
}

int	 	*analyze_stacks(t_stack *a, t_stack *b)
{
	int	*steps;
	int i;
	int instrs;

	steps = (int*)malloc(sizeof(int) * b->size);
	i = b->size;
	instrs = -1;
	while (--i >= 0)
	{
		if (i >= b->size / 2)
		{
			steps[i] = ++instrs;
		}
		else
		{
			if (!ft_iseven(b->size) && i == (b->size / 2) - 1)
				steps[i--] = instrs--;
			else if (ft_iseven(b->size) && i == (b->size / 2) - 1)
				instrs++;
			steps[i] = instrs--;
		}
		steps[i] += steps_to_a(a, b->data[i]);
	}
	return (steps);
}*/

void	pull_el(t_stack *a, t_stack *b, int index, t_steps *steps)
{

	while (steps[index].b_index < b->size - 1)
	{
		if (steps[index].b_index >= b->size / 2)
		{
			rotate(b);
			write(1, "rb\n", 3);
			steps[index].b_index++;
		}
		else
		{
			reverse_rotate(b);
			write(1, "rrb\n", 4);
			steps[index].b_index--;
			steps[index].b_index = (steps[index].b_index < 0) ? b->size - 1 : steps[index].b_index--;
		}
	}
	while (steps[index].a_index < a->size - 1)
	{
		if (steps[index].a_index >= a->size / 2)
		{
			rotate(a);
			write(1, "ra\n", 3);
			steps[index].a_index++;
		}
		else
		{
			reverse_rotate(a);
			write(1, "rra\n", 4);
			steps[index].a_index--;
			steps[index].a_index = (steps[index].a_index < 0) ? a->size - 1 : steps[index].a_index--;
		}
	}
	push(a, b);
	write(1, "pa\n", 3);
}

int 	analyze_steps(t_steps *steps, int size)
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

void	rotate_n_order(t_stack *stack)
{
	int		min;
	int 	min_value;

	min = find_min_el(stack);
	min_value = stack->data[min];
	while (stack->data[stack->size - 1] != min_value)
	{
		if (min > stack->size / 2)
			rotate(stack);
		else
			reverse_rotate(stack);
	}

}

void	sort_stack(t_stack *a, t_stack *b)
{
	char	*str_instructions;
	t_steps 	*steps;
	int		index;
	t_first_loc	seq;
	seq.min = a->data[2];
	seq.middle = a->data[1];
	seq.max = a->data[0];

	//int k = 7;
	while (b->size )
	{
		int i = b->size; //
		steps = analyze_stacks(a, b, &seq);
		printf("*****************\nb stack's steps:\n");
		while (--i >= 0)
			printf("%i + %i\n", steps[i].b_steps, steps[i].a_steps);
		printf("_\nb\n*****************\n");
		index = analyze_steps(steps, b->size);
		//printf("index: %i\n", index);
		pull_el(a, b, index, steps);
		print_stack(a, b);
		seq.min = a->data[find_min_el(a)];
		seq.max = a->data[find_max_el(a)];
	}
}

void	throw_to_b(t_stack *a, t_stack *b)
{
	int	i;

	i = a->size;
	while (--i > 2)
	{
		push(b, a);
		write(1, "pb\n", 3);
	}
}


void	throw_except(t_stack *a, t_stack *b, t_seq *sorted_seq)
{
	int	i;

	i = a->size;
	while (--i >= 0)
	{
		if (i > sorted_seq->start)
		{
			push(b, a);
			write(1, "pb\n", 3);
		}
		else if (i < sorted_seq->end)
		{
			reverse_rotate(a);
			write(1, "rra\n", 4);
			sorted_seq->start--;
			sorted_seq->end--;
		}
		if (i == 0 && a->size != sorted_seq->amount)
			i = a->size;
	}
}

void	first_sort(t_stack *stack)
{
	if (stack->data[2] > stack->data[1] && stack->data[0] > stack->data[2])
		swap(stack);
	else if (stack->data[2] > stack->data[1] && stack->data[0] < stack->data[2])
		rotate(stack);
	if (stack->data[2] > stack->data[1])
		swap(stack);
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
		throw_to_b(a, b);
	first_sort(a);
	print_stack(a, b);
	sort_stack(a, b);
	rotate_n_order(a);
	print_stack(a, b);
	//printf ("start: %i\tend: %i\tamount: %i\n", sorted_seq->start, sorted_seq->end, sorted_seq->amount);
}