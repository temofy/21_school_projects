/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CleanUp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 20:04:28 by cheller           #+#    #+#             */
/*   Updated: 2019/05/20 20:04:30 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	free_fp(t_float **fp)
{
	free((*fp)->binary);
	free((*fp)->exp);
	free((*fp)->frac);
	free((*fp)->binary_represent);
	free(*fp);
	*fp = NULL;
}

void	free_str_fp(t_str_fp **str_fp)
{
	free((*str_fp)->integer);
	free((*str_fp)->frac);
	free(*str_fp);
	*str_fp = NULL;
}

void	free_e_sequence(t_formatting **e_seq)
{
	if (*e_seq)
	{
		free((*e_seq)->flags);
		free(*e_seq);
	}
}
