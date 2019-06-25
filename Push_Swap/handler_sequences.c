/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sequences.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:23:59 by cheller           #+#    #+#             */
/*   Updated: 2019/06/25 20:25:04 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_seq	*initialize_seq(void)
{
	t_seq	*seq;

	seq = (t_seq*)malloc(sizeof(t_seq));
	seq->amount = 0;
	seq->start = -1;
	seq->end = -1;
	return (seq);
}

void	zero_seq_values(t_seq *seq)
{
	seq->amount = 0;
	seq->start = -1;
	seq->end = -1;
}

void	rewrite_values(t_seq *seq, t_seq *tmp)
{
	seq->amount = tmp->amount;
	seq->start = tmp->start;
	seq->end = tmp->end;
}
