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

int		read_arguments(t_stack *a, int amount, char *argv[])
{
	int 		i;
	int 		j;

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
	return (2);
}

void	print_stack(t_stack *a, t_stack *b)
{
	int i;
	int size_a;
	int size_b;

	i = (a->size > b->size) ? a->size : b->size;
	size_a = a->size;
	size_b = b->size;
	while (--i >= 0)
	{

		if (size_a == i + 1)
		{
			size_a--;
			printf("%d\t", a->data[i]);
		}
		else
			printf(" \t");
		if (size_b == i + 1)
		{
			size_b--;
			printf("%d\n", b->data[i]);
		}
		else
			printf(" \n");
	}
	printf("_\t_\na\tb\n");
}