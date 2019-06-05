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

void	print_stack(t_stack *stack)
{
	int i;
	i = stack->size;

	//printf("size %d\n", stack->size);
	while (--i >= 0)
	{
		printf("%d\n", stack->data[i]);
		/*write(1, stack->data[i], 1);
		write(1, "\n", 1);*/
	}
	printf("_\na\n");
	//write(1, "-\na\n", 4);
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
	if (stack->size < 2)
		return ;
	tmp = stack->data[i - 1];
	while (i < stack->size - 2)
	{
		stack->data[i - 1] = stack->data[stack->size - 1];
		stack->data[stack->size - 1] = tmp;
		tmp = stack->data[i - 2];
		i--;
	}
	stack->data[i - 1] = stack->data[stack->size - 1];
	stack->data[stack->size - 1] = tmp;
}

t_stack	*stack_malloc(int amount)
{
	t_stack	*stack;

	stack = (t_stack*)ft_memalloc(sizeof(t_stack));
	stack->data = ft_memalloc(amount);
	stack->size = 0;
	return (stack);
}

void	select_operation(char *operation, t_stack *a, t_stack *b)
{
	if (ft_strcmp(operation, "sa") == 0)
		swap(a);
	if (ft_strcmp(operation, "sb") == 0)
		swap(b);
	if (ft_strcmp(operation, "ss") == 0)
	{
		swap(a);
		swap(b);
	}
	if (ft_strcmp(operation, "pa") == 0)
		push(a, b);
	if (ft_strcmp(operation, "pb") == 0)
		push(b, a);
	if (ft_strcmp(operation, "ra") == 0)
		rotate(a);
	if (ft_strcmp(operation, "rb") == 0)
		rotate(b);
	if (ft_strcmp(operation, "rr") == 0)
	{
		rotate(a);
		rotate(b);
	}
}
int 	checker(int amount, char *argv[])
{
	t_stack		*a;
	t_stack		*b;

	int 		i;
	int 		j;

	i = 0;
	a = stack_malloc(amount);
	b = stack_malloc(amount);
	while (i < amount)
	{
		if (ft_atopi(argv[i + 1]) == NULL)
			return (-1);
		a->data[i] = *ft_atopi(argv[i + 1]);
		a->size++;
		j = -1;
		while (++j < i)
			if (a->data[j] == a->data[i])
				return (-1);
		i++;
	}
	return (2);
}

int 	main(int argc, char *argv[])
{
	int 	rtn;

	rtn = checker(argc - 1, &*argv);
	if (rtn == -1)
		write(2, "Error\n", 6);
	if (rtn == 1)
		write(1, "KO\n", 3);
	if (rtn == 2)
		write(1, "OK\n", 3);
	return (rtn);
}