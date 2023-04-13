/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 00:37:08 by yahamdan          #+#    #+#             */
/*   Updated: 2023/04/05 00:37:21 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int				i;
	int				s;
	unsigned long	r;

	i = 0;
	s = 1;
	r = 0;
	while ((str[i] && str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while ((str[i] && str[i] >= '0' && str[i] <= '9'))
	{
		r = r * 10 + (str[i++] - '0');
	}
	if (r > LONG_MAX && s == -1)
		return (0);
	if (r > LONG_MAX && s == 1)
		return (-1);
	return (r * s);
}