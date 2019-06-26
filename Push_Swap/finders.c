#include "push_swap.h"

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
				rewrite_values(start_end, tmp);
			zero_seq_values(tmp);
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

int		find_place(t_stack *stack, int value)
{
	int	index;

	index = stack->size - 1;
	while (index > 0)
	{
		if (stack->data[index] < value && stack->data[index - 1] > value)
			return (index - 1);
		index--;
	}
	index = stack->size - 1;
	return (index);
}
