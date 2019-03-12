/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moment.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:48:21 by cheller           #+#    #+#             */
/*   Updated: 2019/03/12 19:32:10 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t		ft_strlen(const char *str)
{
	size_t length;

	length = 0;
	while (str[length] != '\0')
		length++;
	return (length);
}

int		nbr_len(int n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = nbr_len(n) - 1;
	str = (char*)malloc(sizeof(char) * (nbr_len(n) + 1));
	if (!str)
		return (NULL);
	str[nbr_len(n)] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i--] = 48 + (n % 10);
		n /= 10;
	}
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len_s1;
	int		len_s2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (len_s1 + len_s2) + 1)))
		return (NULL);
	while (i < len_s1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len_s1 + len_s2)
	{
		str[i] = s2[i - len_s1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*moment(unsigned int duration)
{
	char	*units_single[5];
	char	*units_multiple[5];
	char	*string;

	int		minutes;
	int		hours;
	int		days;
	int		months;

	minutes = 0;
	hours = 0;
	days = 0;
	months = 0;
	string = NULL;
	units_single[0] = " second ago.";
	units_single[1] = " minute ago.";
	units_single[2] = " hour ago.";
	units_single[3] = " day ago.";
	units_single[4] = " month ago.";

	units_multiple[0] = " seconds ago.";
	units_multiple[1] = " minutes ago.";
	units_multiple[2] = " hours ago.";
	units_multiple[3] = " days ago.";
	units_multiple[4] = " months ago.";

	if (duration == 0)
		return (ft_strjoin("0", units_multiple[0]));
	if (duration == 1)
			return (ft_strjoin("1", units_single[0]));
	if (duration > 0 && duration < 60)
		return (ft_strjoin(ft_itoa(duration), units_multiple[0]));
	if (duration >= 60)
	{
		minutes = duration / 60;
		if (minutes >= 60)
		{
			hours = minutes / 60;
			if (hours >= 24)
			{
				days = hours / 24;
				if (days >= 30)
					months = days / 30;
			}
		}
	}

	if (months == 1)
		return (ft_strjoin("1", units_single[4]));
	else if (months > 1)
		return (ft_strjoin(ft_itoa(months), units_multiple[4]));
	else if (days == 1)
		return (ft_strjoin("1", units_single[3]));
	else if (days > 1)
		return (ft_strjoin(ft_itoa(days), units_multiple[3]));
	else if (hours == 1)
		return (ft_strjoin("1", units_single[2]));
	else if (hours > 1)
		return (ft_strjoin(ft_itoa(hours), units_multiple[2]));
	else if (minutes == 1)
		return (ft_strjoin("1", units_single[1]));
	else if (minutes > 1)
		return (ft_strjoin(ft_itoa(minutes), units_multiple[1]));
	return (string);
}
