/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:00:09 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/06 22:09:39 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\033[0;31m"

typedef struct s_print{
	pthread_mutex_t		print;
	pthread_mutex_t		luck;
}	t_print;

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
	t_print				*print;
	int					nbr_eat;
	pthread_mutex_t		*mutex;
}	t_inf;

void		print_(char *str, t_inf *infrm, int i);
int			ft_atoi(char *str);
long int	time_(void);
void		initialize(t_inf *infrm, char **av, int ac,	t_print *print);
int			check_die(t_inf *inf);
#endif