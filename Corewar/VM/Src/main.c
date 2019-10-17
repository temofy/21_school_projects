/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:05:19 by qmebble           #+#    #+#             */
/*   Updated: 2019/10/16 16:10:14 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/virtual_header.h"

int		main(int argc, char *argv[])
{
	int	rtn;

	rtn = 1;
	if (argc < 2)
	{
		print_usage();
		return (-1);
	}
	else
	{
		initialize_vm();
		rtn = parsing(argc, argv);
		if (rtn == 1)
			virtual_machine();
		free_all();
	}
	return (rtn);
}
