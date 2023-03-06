/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:03:18 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/05 19:12:29 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	initialize_struct(t_inf *infrm, t_sema *sema, char **av, int ac)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		infrm[i].nbr_f = ft_atoi(av[1]);
		infrm[i].time_to_die = ft_atoi(av[2]);
		infrm[i].time_to_eat = ft_atoi(av[3]);
		infrm[i].time_to_sleep = ft_atoi(av[4]);
		infrm[i].nbr_eat = ft_atoi(av[5]);
		infrm[i].sema = sema;
		infrm[i].index = i;
		infrm[i].ac = ac;
		infrm[i].ac_ = ac;
		infrm[i].pid = 0;
		gettimeofday(&infrm[i].last_meal, NULL);
		i++;
	}
}

void	check_exit(t_inf *infrm)
{
	int	exit_;
	int	exit_status;
	int	i;

	i = 0;
	while (i < infrm->nbr_f)
	{
		waitpid(-1, &exit_, 0);
		exit_status = WEXITSTATUS(exit_);
		if (exit_status == 0)
		{
			i = 0;
			while (i < infrm->nbr_f)
			{
				kill(infrm[i].pid, SIGKILL);
				i++;
			}
		}
		i++;
	}
}

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
