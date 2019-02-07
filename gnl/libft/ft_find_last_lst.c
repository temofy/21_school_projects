/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_last_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 18:55:38 by cheller           #+#    #+#             */
/*   Updated: 2019/01/25 19:00:10 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_fd	*ft_find_last_lst(t_list_fd *first_lst)
{
	t_list_fd	*last_lst;

	if (!(first_lst->next_lst))
		return (first_lst);
	last_lst = first_lst;
	while (last_lst->next_lst)
		last_lst = last_lst->next_lst;
	return (last_lst);
}
