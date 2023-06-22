/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:44:10 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/22 13:07:44 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philosopher->lfork);
		ft_print(philosopher, "has taken a lfork");
		pthread_mutex_lock(philosopher->rfork);
		ft_print(philosopher, "has taken a rfork");
		pthread_mutex_lock(philosopher->dlock);
		philosopher->eat_ti = new_time();
		pthread_mutex_unlock(philosopher->dlock);
		ft_print(philosopher, "is eating");
		pthread_mutex_lock(philosopher->mut);
		if (philosopher->ets != 0 && philosopher->ets > 0)
			philosopher->ets--;
		pthread_mutex_unlock(philosopher->mut);
		msleep(new_time(), philosopher->tte);
		pthread_mutex_unlock(philosopher->lfork);
		pthread_mutex_unlock(philosopher->rfork);
		ft_print(philosopher, "is sleeping");
		msleep(new_time(), philosopher->tts);
		ft_print(philosopher, "is thinking");
	}
	return (0);
}

t_philo	*pthrdint(int num, char **av)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * num);
	while (i < num)
	{
		philos[i].id = i + 1;
		philos[i].philosopher = malloc(sizeof(pthread_t));
		philos[i].lfork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philos[i].lfork, NULL);
		i++;
	}
	i = 0;
	while (i < num)
	{
		philos[i].rfork = philos[(i + 1) % num].lfork;
		philos[i].ttd = ft_atoi(av[2]);
		philos[i].tte = ft_atoi(av[3]);
		i++;
	}
	return (philos);
}

void	create_threads(t_philo *philos, int ac, char **av, int num)
{
	long long		current_time;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*dl;
	int				i;

	mutex = malloc(sizeof(pthread_mutex_t));
	dl = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL);
	pthread_mutex_init(dl, NULL);
	current_time = new_time();
	i = 0;
	while (i < num)
	{
		philos[i].tts = ft_atoi(av[4]);
		philos[i].ets = 0;
		if (ac == 6)
			philos[i].ets = ft_atoi(av[5]);
		philos[i].time = current_time;
		philos[i].mut = mutex;
		philos[i].dlock = dl;
		philos[i].eat_ti = new_time();
		pthread_create(&philos->philosopher[i], NULL, &routine, &philos[i]);
		usleep(100);
		i++;
	}
}

int	check_deit(t_philo *philos, int ac, int i, int num)
{
	int	j;

	j = 0;
	while (++i < num)
	{
		pthread_mutex_lock(philos[i].dlock);
		if (new_time() - philos[i].eat_ti >= philos[i].ttd)
		{
			pthread_mutex_lock(philos[i].mut);
			printf("%lld philo %d is died\n",
				new_time() - philos[i].time, i + 1);
			return (1);
		}
		pthread_mutex_unlock(philos[i].dlock);
		if (ac == 6)
		{
			pthread_mutex_lock(philos[i].mut);
			if (philos[i].ets == 0)
				j++;
			if (j == num)
				return (1);
			pthread_mutex_unlock(philos[i].mut);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			*philos;
	int				i;
	int				num;

	if (char_arg(ac, av))
		return (1);
	num = ft_atoi(av[1]);
	philos = pthrdint(num, av);
	create_threads(philos, ac, av, num);
	while (1)
	{
		i = -1;
		if (check_deit(philos, ac, i, num))
			return (1);
	}
	return (0);
}
