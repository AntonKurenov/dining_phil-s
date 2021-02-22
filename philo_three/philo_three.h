/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:28:57 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/22 16:37:45 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct timeval	t_time;

typedef struct	s_phil
{
	size_t		start_time;
	size_t		last_eat;
	sem_t		*waiter;
	sem_t		*forks;
	sem_t		*print;
	int			num;
	size_t		tt_die;
	size_t		tt_eat;
	size_t		tt_sleep;
	int			eat_count;
	int			*someone_died;
	int			ph_num;
}				t_phil;

typedef struct	s_main
{
	int			ph_num;
	size_t		tt_die;
	size_t		tt_eat;
	size_t		tt_sleep;
	int			eat_count;
	pthread_t	*observer;
	pthread_t	*phil_thr;
	pid_t		*pids;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*waiter;
	t_phil		*arr_phil;
	int			someone_died;
}				t_main;

void			*observation(void *info);
void			ft_sleep(size_t time);
void			*simulation(void *data);
int				preparation(t_main *data);
void			ft_error(char *str);
int				ft_atoi(char *str);
void			print_error(char *str);
size_t			ft_gettime(void);
int				start(t_main *data);
int				start_threads(t_main *data);
void			print_state(int type, t_phil *phil);

#endif
