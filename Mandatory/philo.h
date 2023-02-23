/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:00:09 by aahrach           #+#    #+#             */
/*   Updated: 2023/02/23 20:22:41 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

// typedef struct s_mutex{
// 	pthread_mutex_t		m;
// }	t_mutex;

//pthread_mutex_t		m;

typedef struct s_inf{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	long int			time_of_day;
	long int			time_creat;
	int					index;
	long int			last_meal;
	long int			last_sleep;
	int					nbr_f;
	int					ac;
	pthread_mutex_t		*mutex_a;
	int					nbr_eat;
	pthread_mutex_t		*mutex;
}	t_inf;

void		print_(char *str, t_inf *infrm);
int			ft_atoi(char *str);
long int	time_(void);
void		initialize(t_inf *infrm, char **av, int ac, pthread_mutex_t *m);
int			check_die(t_inf *inf);
#endif