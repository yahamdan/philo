/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:44:10 by yahamdan          #+#    #+#             */
/*   Updated: 2023/04/15 05:36:56 by yahamdan         ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philosopher->lfork);
		ft_print(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->rfork);
		ft_print(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->dlock);
		philosopher->eat_ti = new_time();
		pthread_mutex_unlock(philosopher->dlock);
		ft_print(philosopher, "is eating");
		msleep(new_time(), philosopher->tte);
		pthread_mutex_unlock(philosopher->lfork);
		pthread_mutex_unlock(philosopher->rfork);
		ft_print(philosopher, "is sleeping");
		msleep(new_time(), philosopher->tts);
		ft_print(philosopher, "is thinking");
		pthread_mutex_lock(philosopher->mut);
		if (philosopher->ets != 0 && philosopher->ets > 0)
			philosopher->ets--;
		pthread_mutex_unlock(philosopher->mut);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			*philos;
	pthread_mutex_t	mutex;
	pthread_mutex_t	dl;
	int				i;
	int				j;
	int				num;
	long long		current_time;

	current_time = new_time();
	num = ft_atoi(av[1]);
	philos = malloc(sizeof(t_philo) * num);
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&dl, NULL);
	i = 0;
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
		philos[i].rfork = philos[(1 + i) % num].lfork;
		i++;
	}
	i = 0;
	while (i < num)
	{
		philos[i].ttd = ft_atoi(av[2]);
		philos[i].tte = ft_atoi(av[3]);
		philos[i].tts = ft_atoi(av[4]);
		philos[i].ets = 0;
		if (ac == 6)
			philos[i].ets = ft_atoi(av[5]);
		philos[i].time = current_time;
		philos[i].mut = &mutex;
		philos[i].dlock = &dl;
		philos[i].eat_ti = new_time();
		pthread_create(&philos->philosopher[i], NULL, &routine, &philos[i]);
		usleep(100);
		i++;
	}
	while (1)
	{
		i = 0;
		j = 0;
		while (i < num)
		{
			pthread_mutex_lock(philos[i].dlock);
			if (new_time() - philos[i].eat_ti >= philos[i].ttd)
			{
				pthread_mutex_lock(philos[i].mut);
				printf("%lld philo %d is died\n", new_time() - philos[i].time, i + 1);
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
			i++;
		}
	}
	return (0);
}
