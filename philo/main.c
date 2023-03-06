/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:59:51 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/06 23:10:53 by aahrach          ###   ########.fr       */
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

void	ft_helpe(t_inf	*infrm)
{
	infrm->last_sleep = time_();
	while (time_() - infrm->last_sleep < infrm->time_to_sleep)
		usleep(100);
	print_("is thinking", infrm, 0);

}

void	*ft_function(void	*inf)
{
	t_inf	*infrm;

	infrm = (t_inf *)inf;
	while (1)
	{
		pthread_mutex_lock(&infrm->mutex[infrm->index]);
		print_("has taken a fork", infrm, 0);
		pthread_mutex_lock(&infrm->mutex[(infrm->index + 1) % infrm->nbr_f]);
		print_("has taken a fork", infrm, 0);
		print_("is eating", infrm, 0);
		pthread_mutex_lock(&infrm[0].print->luck);
		infrm->last_meal = time_();
		if (infrm->nbr_eat > 0)
			infrm->nbr_eat--;
		pthread_mutex_unlock(&infrm[0].print->luck);
		while (time_() - infrm->last_meal < infrm->time_to_eat)
			usleep(100);
		pthread_mutex_unlock(&infrm->mutex[infrm->index]);
		pthread_mutex_unlock(&infrm->mutex[(infrm->index + 1) % infrm->nbr_f]);
		if (infrm->nbr_eat == 0)
			return (NULL);
		print_("is sleeping", infrm, 0);
		ft_helpe(infrm);
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
		usleep(50);
		i++;
	}
	i = 0;
	while (i < infrm->nbr_f)
	{
		pthread_detach(th[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	pthread_t		*th;
	t_inf			*infrm;
	t_print			*print;
	int				i;

	if (ac < 5 || ac > 6)
	{
		write (2, "Error: incorrect number of arguments!\n", 37);
		return (0);
	}
	if (check_argument(av))
		return (0);
	if (ft_atoi(av[1]) == 0 || ft_atoi(av[5]) == 0)
		return (0);
	th = malloc(ft_atoi(av[1]) * sizeof(pthread_t));
	infrm = malloc(ft_atoi(av[1]) * sizeof(t_inf));
	print = malloc(sizeof(t_print));
	pthread_mutex_init(&print->luck, NULL);
	pthread_mutex_init(&print->print, NULL);
	initialize(infrm, av, ac, print);
	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_mutex_init(&(infrm + i)->mutex[i], NULL);
	creat_philo(infrm, th);
	check_die(infrm);
	return (0);
}
