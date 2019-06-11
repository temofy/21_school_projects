#include "push_swap.h"

void	swap(t_stack *stack)
{
	int tmp;

	if (stack->size < 2)
		return ;
	tmp = stack->data[stack->size - 1];
	stack->data[stack->size - 1] = stack->data[stack->size - 2];
	stack->data[stack->size - 2] = tmp;
}

void	push(t_stack *in, t_stack *out)
{
	if (out->size != 0)
	{
		out->size--;
		in->data[in->size] = out->data[out->size];
		in->size++;
	}
}

void	rotate(t_stack *stack)
{
	int i;
	int tmp;

	i = 0;
	if (stack->size < 2)
		return ;
	tmp = stack->data[i + 1];
	while (i < stack->size - 2)
	{
		stack->data[i + 1] = stack->data[0];
		stack->data[0] = tmp;
		tmp = stack->data[i + 2];
		i++;
	}
	stack->data[i + 1] = stack->data[0];
	stack->data[0] = tmp;
}

void	reverse_rotate(t_stack *stack)
{
	int i;
	int tmp;

	i = stack->size - 1;
	if (stack->size < 1)
		return ;
	tmp = stack->data[i - 1];
	while (i > 0)
	{
		stack->data[i - 1] = stack->data[stack->size - 1];
		stack->data[stack->size - 1] = tmp;
		tmp = stack->data[i - 2];
		i--;
	}
}

int 	select_mul_operation(char *operation, t_stack *a, t_stack *b)
{
	if (ft_strcmp(operation, "rr") == 0)
	{
		rotate(a);
		rotate(b);
	}
	else if (ft_strcmp(operation, "rrr") == 0)
	{
		reverse_rotate(a);
		reverse_rotate(b);
	}
	else
	{
		free(operation);
		return (-1);
	}
	free(operation);
	return (1);
}

int		select_operation(char *operation, t_stack *a, t_stack *b)
{
	if (ft_strcmp(operation, "sa") == 0)
		swap(a);
	else if (ft_strcmp(operation, "sb") == 0)
		swap(b);
	else if (ft_strcmp(operation, "ss") == 0)
	{
		swap(a);
		swap(b);
	}
	else if (ft_strcmp(operation, "pa") == 0)
		push(a, b);
	else if (ft_strcmp(operation, "pb") == 0)
		push(b, a);
	else if (ft_strcmp(operation, "ra") == 0)
		rotate(a);
	else if (ft_strcmp(operation, "rb") == 0)
		rotate(b);
	else if (ft_strcmp(operation, "rra") == 0)
		reverse_rotate(a);
	else if (ft_strcmp(operation, "rrb") == 0)
		reverse_rotate(b);
	return (select_mul_operation(operation, a, b));
}