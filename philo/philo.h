/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:43:09 by yahamdan          #+#    #+#             */
/*   Updated: 2023/06/10 10:28:35 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct philo
{
	long long		time;
	int				id;
	pthread_t		*philosopher;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*mut;
	pthread_mutex_t	*dlock;
	pthread_mutex_t *locked;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	ttd;
	long long		eat_ti;
	int				ets;
}	t_philo;

int	ft_atoi(char *str);

#endif