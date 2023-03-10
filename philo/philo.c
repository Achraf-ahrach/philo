/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:34:18 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/06 22:55:33 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	if (!str)
		return (-1);
	if (str[i] == '\0')
		return (0);
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i] - 48);
		i++;
	}
	if (nbr > 2147483647)
		return (-1);
	return (nbr);
}

void	print_(char *str, t_inf *infrm, int i)
{
	pthread_mutex_lock(&infrm->print->print);
	if (i == 1)
	{
		printf("%s%ld ms %d died\n", RED, time_() - infrm->time_creat, \
				infrm->index + 1);
		return ;
	}
	else
	{
		printf("%ld ms %d %s\n", time_() - infrm->time_creat, \
			infrm->index + 1, str);
	}
	pthread_mutex_unlock(&infrm->print->print);
}

long int	time_(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	initialize(t_inf *infrm, char **av, int ac,	t_print *print)
{
	pthread_mutex_t	*forks;
	long int		time_of_creat;
	int				i;

	i = 0;
	time_of_creat = time_();
	forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	while (i < ft_atoi(av[1]))
	{
		infrm[i].time_of_day = time_();
		infrm[i].time_to_die = ft_atoi(av[2]);
		infrm[i].time_to_eat = ft_atoi(av[3]);
		infrm[i].time_to_sleep = ft_atoi(av[4]);
		infrm[i].index = i;
		infrm[i].nbr_eat = ft_atoi(av[5]);
		infrm[i].nbr_f = ft_atoi(av[1]);
		infrm[i].ac = ac;
		infrm[i].mutex = forks;
		infrm[i].print = print;
		i++;
	}
}

int	check_die(t_inf *inf)
{
	int		i;
	int		j;

	while (1)
	{
		i = -1;
		j = 0;
		while (++i < inf[0].nbr_f)
		{
			pthread_mutex_lock(&inf[0].print->luck);
			if (inf[i].ac == 6 && inf[i].nbr_eat == 0)
				j++;
			if (j == inf[i].nbr_f)
				return (0);
			if (time_() - inf[i].last_meal >= inf[i].time_to_die)
			{
				print_("", inf, 1);
				return (0);
			}
			pthread_mutex_unlock(&inf[0].print->luck);
		}
	}
	return (0);
}
