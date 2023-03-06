/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:22:33 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/05 19:08:44 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_(char *str, t_inf *infrm)
{
	sem_wait(infrm->sema->ft_print);
	printf("%ld ms %d %s\n", time_() - infrm->time_creat, \
		infrm->index + 1, str);
	sem_post(infrm->sema->ft_print);
}

void	check_die(t_inf *inf)
{
	int		i;

	i = 0;
	while (1)
	{
		if (inf->ac == 6 && inf->nbr_eat == 0)
			exit (inf->index + 1);
		if (time_() - ((inf->last_meal.tv_sec * 1000)
				+ (inf->last_meal.tv_usec / 1000)) >= inf->time_to_die)
		{
			sem_wait(inf->sema->ft_print);
			printf("%s%ld ms %d died\n", RED, time_() - inf->time_creat, \
				inf->index + 1);
			exit (0);
		}
	}
}

void	help(t_inf *infrm)
{
	sem_post(infrm->sema->forks);
	sem_post(infrm->sema->forks);
	print_("is sleeping", infrm);
	infrm->last_sleep = time_();
	while (time_() - infrm->last_sleep < infrm->time_to_sleep)
		usleep(100);
	print_("is thinking", infrm);
}

void	*ft_function(void	*inf)
{
	t_inf	*infrm;

	infrm = (t_inf *)inf;
	while (1)
	{
		sem_wait(infrm->sema->forks);
		print_("has taken a fork", infrm);
		sem_wait(infrm->sema->forks);
		print_("has taken a fork", infrm);
		print_("is eating", infrm);
		gettimeofday(&infrm->last_meal, NULL);
		if (infrm->nbr_eat > 0)
			infrm->nbr_eat--;
		if (infrm->nbr_eat == 0)
		{
			sem_post(infrm->sema->forks);
			sem_post(infrm->sema->forks);
			return (NULL);
		}
		while (time_() - ((infrm->last_meal.tv_sec * 1000)
				+ (infrm->last_meal.tv_usec / 1000)) < infrm->time_to_eat)
			usleep(100);
		help(infrm);
	}
	return (NULL);
}

void	childe(t_inf *infrm)
{
	pthread_t	th;

	pthread_create(&th, NULL, ft_function, infrm);
	pthread_detach(th);
	check_die(infrm);
}
