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

typedef struct	s_sorted_seq
{
	int	start;
	int	end;
	int	amount;
}				t_seq;

typedef struct	s_steps
{
	int	a_steps;
	int a_index;
	int b_steps;
	int	b_index;
	int	total;
}				t_steps;

typedef struct	s_first_location
{
	int	min;
	int	middle;
	int	max;
}				t_first_loc;

t_stack			*stack_malloc(int amount);
int				is_sorted_stack(t_stack *a, t_stack *b);
void			free_stack(t_stack *stack);
int				reverse_rotate(t_stack *stack);
int				rotate(t_stack *stack);
int				push(t_stack *in, t_stack *out);
int				swap(t_stack *stack);
int				select_operation(char *operation, t_stack *a, t_stack *b);
int				read_arguments(t_stack *a, int amount, char *argv[]);
void			initialize_start(t_stack *a, t_stack *b);
int				find_max_el(t_stack *stack);
int				find_min_el(t_stack *stack);
t_seq			*find_sorted_seq(t_stack *stack);
int				find_boundaries(t_first_loc *seq, int cur_val);
int				find_place(t_stack *stack, int value);
void			print_stack(t_stack *a, t_stack *b);
t_seq			*initialize_seq(void);
void			zero_seq_values(t_seq *seq);
void			rewrite_values(t_seq *seq, t_seq *tmp);
int				analyze_steps(t_steps *steps, int size);
t_steps			*analyze_stacks(t_stack *a, t_stack *b, t_first_loc *seq);
void			steps_to_a(t_stack *a, int val, t_steps *steps,\
t_first_loc *seq);
int				count_steps_i(t_stack *a, int index);
void			pull_el(t_stack *a, t_stack *b, int index, t_steps *steps);
void			rotate_n_order(t_stack *stack);
void			throw_to_b(t_stack *a, t_stack *b);
void			throw_except(t_stack *a, t_stack *b, t_seq *sorted_seq);

#endif
