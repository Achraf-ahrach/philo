/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahrach <aahrach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:02:10 by aahrach           #+#    #+#             */
/*   Updated: 2023/03/05 22:23:40 by aahrach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdatomic.h>

# define RED "\033[0;31m"

typedef struct s_sema{
	sem_t				*forks;
	sem_t				*ft_print;
}	t_sema;

typedef struct s_inf{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_f;
	t_sema				*sema;
	pid_t				pid;
	long				time_creat;
	int					index;
	struct timeval		last_meal;
	long				last_sleep;
	int					ac;
	int					ac_;
	atomic_int			nbr_eat;
}	t_inf;

void		print_(char *str, t_inf *infrm);
int			ft_atoi(char *str);
long int	time_(void);
void		check_die(t_inf *inf);
void		childe(t_inf *infrm);
void		initialize_struct(t_inf *infrm, t_sema *sema, char **av, int ac);
void		check_exit(t_inf *infrm);
#endif