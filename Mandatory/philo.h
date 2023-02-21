/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:00:09 by aahrach           #+#    #+#             */
/*   Updated: 2023/02/21 16:20:03 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_inf{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	long int			time_of_day;
	long int			time_creat;
	int					index;
	long int			last_meal;
	int					nbr_f;
	int					nbr_eat;
	pthread_mutex_t		*mutex;
}	t_inf;

int			ft_atoi(char *str);
long int	time_(void);
void		initialize(t_inf *infrm, char **av);
int			check_die(t_inf *inf);
#endif