/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:34:18 by aahrach           #+#    #+#             */
/*   Updated: 2023/02/21 16:15:29 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	time_(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	initialize(t_inf *infrm, char **av)
{
	pthread_mutex_t	*forks;
	long int		time_of_creat;
	int				i;

	i = 0;
	time_of_creat = time_();
	forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	while (i < ft_atoi(av[1]))
	{
		(infrm + i)->time_of_day = time_();
		(infrm + i)->time_to_die = ft_atoi(av[2]);
		(infrm + i)->time_to_eat = ft_atoi(av[3]);
		(infrm + i)->time_to_sleep = ft_atoi(av[4]);
		(infrm + i)->index = i;
		(infrm + i)->nbr_eat = ft_atoi(av[5]);
		(infrm + i)->nbr_f = ft_atoi(av[1]);
		(infrm + i)->mutex = forks;
		i++;
	}
}

int	check_die(t_inf *inf)
{
	int		i;
	int		s;
	long	t_day_t_creat;

	s = 0;
	while (1)
	{
		i = 0;
		while (i < inf->nbr_f)
		{
			t_day_t_creat = time_() - inf[i].time_creat;
			if (time_() - inf[i].last_meal >= inf[i].time_to_die)
			{
				if (inf[i].nbr_eat == 0)
					return (0);
				printf("%ld ms %d died\n", t_day_t_creat, inf[i].index + 1);
				return (0);
			}
			i++;
		}
	}
}
