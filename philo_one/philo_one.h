/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:28:57 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/17 16:23:43 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

// pthread_create(&t1, NULL, &function, arg) return 0 if successful

typedef pthread_mutex_t mutex_t;
typedef struct timeval t_time;

struct s_main;

typedef struct s_phil
{
	struct s_main	*data;
	size_t	start_life;
	size_t 	time_death;
	size_t	start_time;
	size_t	last_eat;
	size_t	time_diff;
	size_t	time_of_death;
	int			is_dead;
	mutex_t		*left_fork;
	mutex_t		*right_fork;
	mutex_t		*print;
	int 		ph_num;
	int			num;
	int 		tt_die;
	int 		tt_eat;
	int 		tt_sleep;
	int 		eat_count;
}			t_phil;

typedef struct s_main
{
	int			ph_num;
	size_t		tt_die;
	size_t		tt_eat;
	size_t		tt_sleep;
	int			eat_count;
	pthread_t	*observer;
	pthread_t	*phil_thr;
	mutex_t		*forks;
	mutex_t		*print;
	t_phil		*arr_phil;
	int			someone_died;
}				t_main;

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