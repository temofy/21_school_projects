/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 13:58:37 by cheller           #+#    #+#             */
/*   Updated: 2019/03/27 15:52:11 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int		ascending(int a, int b)
{
	return (a <= b);
}

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{

	return (lst);
}

t_list	*lst_new(void *data, t_list *next)
{
	t_list	*lst;

	if(!(lst = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	lst->data = data;
	lst->next = next;
	return (lst);
}

void	print_lsts(t_list *lst)
{
	
}

int		main()
{
	t_list	*lst;
	void		*data;
	int			a;

	//a = 5;
	//data = (void*)a;
	printf("%zu\n", ;
	lst = lst_new("string3", NULL);
	lst = lst_new("string2", lst);
	lst = lst_new("string", lst);

	printf("result: %d\n", ascending(15, 10));
	return (1);
}
