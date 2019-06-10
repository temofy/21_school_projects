/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:43:29 by cheller           #+#    #+#             */
/*   Updated: 2019/06/05 13:43:46 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

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

t_stack	*stack_malloc(int amount)
{
	t_stack	*stack;

	stack = (t_stack*)ft_memalloc(sizeof(t_stack));
	stack->data = ft_memalloc(amount * sizeof(int));
	stack->size = 0;
	return (stack);
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
	else if (ft_strcmp(operation, "rr") == 0)
	{
		rotate(a);
		rotate(b);
	}
	else if (ft_strcmp(operation, "rra") == 0)
		reverse_rotate(a);
	else if (ft_strcmp(operation, "rrb") == 0)
		reverse_rotate(b);
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

int 	is_sorted_stack(t_stack *a, t_stack *b)
{
	int		i;

	if (b->size)
		return (1);
	i = a->size - 1;
	while(i > 0)
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

int 	checker(int amount, char *argv[])
{
	t_stack		*a;
	t_stack		*b;
	int 		rtn;
	char 		*operation;

	a = stack_malloc(amount);
	b = stack_malloc(amount);
	if ((rtn = read_arguments(a, amount, &*argv)) == -1)
		return (rtn);
	while (get_next_line(0, &operation))
	{
		if (ft_strcmp(operation, ""))
		{
			if ((select_operation(operation, a, b)) == -1)
				return (-1);
			//print_stack(a, b);
		}
		else
		{
			free(operation);
			break;
		}
	}
	rtn = is_sorted_stack(a, b);
	//print_stack(a, b);
	free_stack(a);
	free_stack(b);
	return (rtn);
}

int 	main(int argc, char *argv[])
{
	int 	rtn;

	if (argc == 1)
		return (0);
	rtn = checker(argc - 1, &*argv);
	if (rtn == -1)
		write(2, "Error\n", 6);
	if (rtn == 1)
		write(1, "KO\n", 3);
	if (rtn == 2)
		write(1, "OK\n", 3);
	return (rtn);
}
