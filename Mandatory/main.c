/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:59:51 by aahrach           #+#    #+#             */
/*   Updated: 2023/02/21 16:16:08 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argument(char **av)
{
	int	y;
	int	x;

	y = 0;
	while (av[++y])
	{
		x = 0;
		if (av[y][x] == '+')
			x++;
		while (av[y][x])
		{
			if (av[y][x] < '0' || av[y][x] > '9')
			{
				write (2, "Error!\n", 8);
				return (1);
			}
			x++;
		}
		if (ft_atoi(av[y]) == -1)
		{
			write (1, "Error!\n", 8);
			return (1);
		}
	}
	return (0);
}

void	*ft_function(void	*inf)
{
	t_inf	*infrm;
	long	i;

	infrm = (t_inf *)inf;
	i = infrm->time_creat;
	while (1)
	{
		pthread_mutex_lock(&infrm->mutex[infrm->index]);
		printf("%ld ms %d has taken a fork\n", time_() - i, infrm->index + 1);
		pthread_mutex_lock(&infrm->mutex[(infrm->index + 1) % infrm->nbr_f]);
		printf("%ld ms %d has taken a fork\n", time_() - i, infrm->index + 1);
		infrm->last_meal = time_();
		if (infrm->nbr_eat > 0)
			infrm->nbr_eat--;
		printf("%ld ms %d is eating\n", time_() - i, infrm->index + 1);
		usleep(infrm->time_to_eat * 1000);
		pthread_mutex_unlock(&infrm->mutex[infrm->index]);
		pthread_mutex_unlock(&infrm->mutex[(infrm->index + 1) % infrm->nbr_f]);
		if (infrm->nbr_eat == 0)
			return (NULL);
		printf("%ld ms %d is sleeping\n", time_() - i, infrm->index + 1);
		usleep(infrm->time_to_sleep * 1000);
		printf("%ld ms %d is thinking\n", time_() - i, infrm->index + 1);
	}
	return (NULL);
}

void	creat_philo(t_inf *infrm, pthread_t	*th)
{
	int	i;

	i = 0;
	infrm[i].time_creat = time_();
	while (i < infrm->nbr_f)
	{
		infrm[i].time_creat = infrm[0].time_creat;
		infrm[i].last_meal = infrm[0].time_creat;
		if (pthread_create(th + i, NULL, ft_function, &infrm[i]) == -1)
		{
			printf("Error\n");
			return ;
		}
		pthread_detach(th[i]);
		usleep(100);
		i++;
	}
}

int	main(int ac, char **av)
{
	pthread_t	*th;
	t_inf		*infrm;
	int			i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		write (2, "Error: incorrect number of arguments!\n", 37);
		return (0);
	}
	if (check_argument(av))
		return (0);
	th = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	infrm = malloc(ft_atoi(av[1]) * sizeof(t_inf));
	initialize(infrm, av);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&(infrm + i)->mutex[i], NULL);
		i++;
	}
	creat_philo(infrm, th);
	check_die(infrm);
	system("leaks philo");
}
