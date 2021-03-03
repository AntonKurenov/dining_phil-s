/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:28:57 by elovegoo          #+#    #+#             */
/*   Updated: 2021/03/03 14:05:14 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;

typedef struct		s_phil
{
	int				*someone_died;
	int				*finished;
	int				ended;
	size_t			start_time;
	size_t			last_eat;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	t_mutex			*print;
	int				ph_num;
	int				num;
	size_t			tt_die;
	size_t			tt_eat;
	size_t			tt_sleep;
	int				eat_count;
}					t_phil;

typedef struct		s_main
{
	int				ph_num;
	size_t			tt_die;
	size_t			tt_eat;
	size_t			tt_sleep;
	size_t			start_time;
	int				eat_count;
	pthread_t		*phil_thr;
	t_mutex			*forks;
	t_mutex			*print;
	t_phil			*arr_phil;
	int				someone_died;
	int				finished;
}					t_main;

void				ft_sleep(size_t time);
void				*simulation(void *data);
int					preparation(t_main *data);
void				ft_error(char *str);
int					ft_atoi(char *str);
void				print_error(char *str);
size_t				ft_gettime(void);
int					start(t_main *data);
int					start_threads(t_main *data);

#endif
