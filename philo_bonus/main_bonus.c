/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:22:52 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/05 19:14:18 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int	time_(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

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

void	initialize(t_inf *infrm, char **av, int ac)
{
	t_sema			*sema;

	sema = malloc(sizeof(t_sema));
	sem_unlink("forks");
	sem_unlink("ft_print");
	sema->forks = sem_open("forks", O_CREAT, 0666, ft_atoi(av[1]));
	sema->ft_print = sem_open("ft_print", O_CREAT, 0666, 1);
	if (sema->forks == SEM_FAILED || sema->ft_print == SEM_FAILED)
	{
		printf("Error in sem_open\n");
		exit (1);
	}
	initialize_struct(infrm, sema, av, ac);
}

void	check_error(char **av, int ac)
{
	if (ac < 5 || ac > 6)
	{
		write (2, "Error: incorrect number of arguments!\n", 37);
		exit (1);
	}
	if (check_argument(av))
		exit (1);
	if (ft_atoi(av[1]) == 0 || ft_atoi(av[5]) == 0)
		exit (1);
}

int	main(int ac, char **av)
{
	t_inf			*infrm;
	int				i;

	check_error(av, ac);
	infrm = malloc(ft_atoi(av[1]) * sizeof(t_inf));
	initialize(infrm, av, ac);
	i = -1;
	while (++i < infrm->nbr_f)
	{
		infrm[i].time_creat = time_();
		infrm[i].pid = fork();
		if (infrm[i].pid == -1)
		{
			i = -1;
			while (++i < infrm->nbr_f)
				kill(infrm[i].pid, SIGKILL);
			exit (1);
		}
		else if (infrm[i].pid == 0)
			childe(&infrm[i]);
	}
	check_exit(infrm);
}
