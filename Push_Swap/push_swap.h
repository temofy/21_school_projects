/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:43:42 by cheller           #+#    #+#             */
/*   Updated: 2019/06/05 13:43:43 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct	s_stack
{
	int			*data;
	size_t		size;
}				t_stack;

t_stack			*stack_malloc(int amount);
int				is_sorted_stack(t_stack *a, t_stack *b);
void			free_stack(t_stack *stack);
void			reverse_rotate(t_stack *stack);
void			rotate(t_stack *stack);
void			push(t_stack *in, t_stack *out);
void			swap(t_stack *stack);
int				select_operation(char *operation, t_stack *a, t_stack *b);
int				read_arguments(t_stack *a, int amount, char *argv[]);
int 	find_max_el(t_stack *stack);
int 	find_min_el(t_stack *stack);

void	print_stack(t_stack *a, t_stack *b);

#endif
