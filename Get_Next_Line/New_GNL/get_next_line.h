/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 12:12:53 by cheller           #+#    #+#             */
/*   Updated: 2019/02/07 19:33:59 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 50000
# define PENULT_CHR buff[BUFF_SIZE - 1] == '\n' && i == BUFF_SIZE - 1
# include "libft/libft.h"

int		get_next_line(const int fd, char **line);

#endif
