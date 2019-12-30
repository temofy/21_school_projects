/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:52:06 by cheller           #+#    #+#             */
/*   Updated: 2019/01/24 17:10:01 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_fd		*ft_lstnew_fd(int fd, char *tmp)
{
	t_list_fd	*lstnew;

	if (!(lstnew = (t_list_fd*)malloc(sizeof(t_list_fd))))
		return (NULL);
	lstnew->fd = fd;
	lstnew->tmp_line = tmp;
	lstnew->next_lst = NULL;
	return (lstnew);
}
