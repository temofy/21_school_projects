/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:43:29 by cheller           #+#    #+#             */
/*   Updated: 2019/06/26 12:48:13 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stacks(t_stack *a, t_stack *b)
{
	free_stack(a);
	free_stack(b);
}

int		checker(int amount, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	int			rtn;
	char		*operation;

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
		}
		else
		{
			ft_strdel(&operation);
			break ;
		}
	}
	rtn = is_sorted_stack(a, b);
	free_stacks(a, b);
	return (rtn);
}

int		main(int argc, char *argv[])
{
	int		rtn;
	char	**instructions;

	if (argc == 1)
		return (0);
	if (argc == 2)
	{
		instructions = ft_strsplit(argv[1], ' ');
		if (ft_arraylen((void**)instructions) == 0)
		{
			ft_arrdel(&instructions);
			return (0);
		}
		rtn = checker(ft_arraylen((void**)instructions), instructions - 1);
		ft_arrdel(&instructions);
	}
	else
		rtn = checker(argc - 1, &*argv);
	if (rtn == -1)
		write(2, "Error\n", 6);
	if (rtn == 1)
		write(1, "KO\n", 3);
	if (rtn == 2)
		write(1, "OK\n", 3);
	return (rtn);
}
