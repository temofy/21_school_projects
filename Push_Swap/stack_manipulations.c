#include "push_swap.h"

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
