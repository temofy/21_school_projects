/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 17:28:28 by cheller           #+#    #+#             */
/*   Updated: 2018/12/26 18:29:59 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*begin;

	if (!lst)
		return (NULL);
	new_lst = f(lst);
	begin = new_lst;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new_lst->next = f(lst)))
		{
			free(new_lst->next);
			return (NULL);
		}
		new_lst = new_lst->next;
	}
	return (begin);
}
