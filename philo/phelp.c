/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phelp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:48:45 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/22 13:26:56 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	new_time(void)
{
	long long		t;
	struct timeval	timv;

	gettimeofday(&timv, NULL);
	t = timv.tv_sec * 1000 + timv.tv_usec / 1000;
	return (t);
}

void	msleep(unsigned long new, unsigned long n)
{
	while (new_time() - new < n)
		usleep(100);
}

void	ft_print(t_philo *p, char *s)
{
	pthread_mutex_lock(p->mut);
	printf("%lld philo %d %s\n", new_time() - p->time, p->id, s);
	pthread_mutex_unlock(p->mut);
}

int	ft_isdigit(char *ar)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		if (!(ar[i] >= '0' && ar[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	char_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5)
		return (1);
	if (ac == 5 || ac == 6)
	{
		while (av[i])
		{
			if (ft_isdigit(av[i]))
				return (1);
			i++;
		}
		i = 1;
		while (av[i])
		{
			if (ft_atoi(av[i]) == 0)
				return (1);
			i++;
		}
	}
	return (0);
}
