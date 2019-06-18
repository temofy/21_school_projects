#include "push_swap.h"

typedef struct s_sorted_seq
{
	int		start;
	int 	end;
	int 	amount;
}				t_seq;


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

int 	steps_to_a(t_stack *a, int value)
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
}

void	pull_el(t_stack *a, t_stack *b, index)
{
	while (index < b->size - 1)
	{

	}
	push(a, b);
	write(1, "pa\n", 3);
}

int 	analyze_steps(int *steps, int size)
{
	int i;
	int min;
	int index;

	i = 0;
	min = steps[0];
	index = 0;
	while (++i < size)
	{
		if (min > steps[i])
		{
			min = steps[i];
			index = i;
		}
	}
	return (index);
}

void	sort_stack(t_stack *a, t_stack *b)
{
	char	*str_instructions;
	int 	*steps;
	int 	i = b->size; //
	int		index;

	steps = analyze_stacks(a, b);
	printf("b stack's steps:\n");
	while (--i >= 0)
		printf("%i\n", steps[i]);
	printf("_\nb\n");
	index = analyze_steps(steps, b->size);
	printf("index: %i\n", index);
	pull_el(a, b, index);
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
	//printf ("start: %i\tend: %i\tamount: %i\n", sorted_seq->start, sorted_seq->end, sorted_seq->amount);
}