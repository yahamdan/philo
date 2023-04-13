/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:44:10 by yahamdan          #+#    #+#             */
/*   Updated: 2023/04/13 03:40:00 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t global_mutex;

long long new_time()
{
	long long	t;
	struct timeval timv;

	gettimeofday(&timv, NULL);
	t = timv.tv_sec * 1000 + timv.tv_usec / 1000;
	return (t);
}

void	msleep(unsigned long new, unsigned long n)
{
	while (new_time() - new < n)
		usleep(100);
}


void	ft_print(philo *p, int i)
{
	pthread_mutex_lock(p->mut);
	if (i == 0)
		printf("%lld philo %d has taken a fork \n", new_time() - p->time,  p->id);
	else if (i == 1)
		printf("%lld philo %d is eating\n", new_time() - p->time, p->id);
	else if (i == 2)
		printf("%lld philo %d is sleeping\n", new_time() - p->time, p->id);
	else if (i == 3)
		printf("%lld philo %d is thinking\n", new_time() - p->time, p->id);
	pthread_mutex_unlock(p->mut);
}

void*    routine(void *arg)
{
	philo *philosopher = (philo *)arg;
	while(1)
	{
		pthread_mutex_lock(philosopher->lfork);
		ft_print(philosopher, 0);
		pthread_mutex_lock(philosopher->rfork);
		ft_print(philosopher, 0);
		pthread_mutex_lock(philosopher->dlock);
		philosopher->eat_ti = new_time();
		pthread_mutex_unlock(philosopher->dlock);
		ft_print(philosopher, 1);
		msleep(new_time(), philosopher->tte);
		pthread_mutex_unlock(philosopher->lfork);
		pthread_mutex_unlock(philosopher->rfork);
		ft_print(philosopher, 2);
		msleep(new_time(), philosopher->tts);
		ft_print(philosopher, 3);
		pthread_mutex_lock(philosopher->dlock);
		if (philosopher->ets != 0 && philosopher->ets > 0)
			philosopher->ets--;
		pthread_mutex_unlock(philosopher->dlock);
	}
	return (0);
}

int main(int ac, char **av)
{
	philo   *philos;
	pthread_mutex_t mutex;
	pthread_mutex_t	dl;
	int     i;
	int		j;
	int     num;
	long long current_time = new_time();

	num = ft_atoi(av[1]);
	philos = malloc(sizeof(philo) * num);
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&dl, NULL);
	i = 0;
	while(i < num)
	{
		philos[i].id = i + 1;
		philos[i].philosopher = malloc(sizeof(pthread_t));
		philos[i].lfork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philos[i].lfork, NULL);
		
		i++;
	}
	i = 0;
	while(i < num)
	{
		philos[i].rfork = philos[(1 + i) % num].lfork;
		i++;
	}
	
	i = 0;
	while(i < num)
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
	while(1)
	{
		i = 0;
		j = 0;
		while (i < num)
		{
			pthread_mutex_lock(philos[i].dlock);
			if (new_time() - philos[i].eat_ti >= philos[i].ttd)
			{
				pthread_mutex_lock(philos[i].mut);
				printf("%lld philo %d is die\n", new_time() - philos[i].time, i + 1);
				return (1);
			}
			pthread_mutex_unlock(philos[i].dlock);
			if (ac == 6)
			{
				if (philos[i].ets == 0)
					j++;
				if (j == num)
					return(1);
			}
			i++;
		}
	}
	return (0);
}
