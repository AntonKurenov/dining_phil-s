/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:37:50 by elovegoo          #+#    #+#             */
/*   Updated: 2021/03/03 15:31:26 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static	void	fill_each_phil(t_main *data, t_phil *phil, int i)
{
	phil->start_time = data->start_time;
	phil->ended = 0;
	phil->ph_num = data->ph_num;
	phil->someone_died = &data->someone_died;
	phil->finished = &data->finished;
	phil->print = data->print;
	phil->num = i;
	phil->eat_count = data->eat_count;
	phil->tt_eat = data->tt_eat;
	phil->tt_sleep = data->tt_sleep;
	phil->tt_die = data->tt_die;
	if (i == data->ph_num)
	{
		phil->left_fork = data->forks + i;
		phil->right_fork = data->forks + 1;
	}
	else
	{
		phil->left_fork = data->forks + i;
		phil->right_fork = data->forks + i + 1;
	}
	if (pthread_mutex_init(phil->left_fork, NULL) || pthread_mutex_init(phil->\
		right_fork, NULL))
		print_error("Failed to initialize mutex");
}

int				preparation(t_main *data)
{
	int			i;
	int			count;

	i = 0;
	count = data->ph_num + 1;
	if (!(data->arr_phil = (t_phil *)malloc(sizeof(t_phil) * count)))
		print_error("Sorry, memory allocation error((");
	if (!(data->forks = (t_mutex *)malloc(sizeof(t_mutex) * count)))
		print_error("Sorry, memory allocation error((");
	if (!(data->print = (t_mutex *)malloc(sizeof(t_mutex))))
		print_error("Sorry, memory allocation error((");
	data->start_time = ft_gettime();
	while (++i <= data->ph_num)
	{
		fill_each_phil(data, data->arr_phil + i, i);
	}
	if (!(data->phil_thr = (pthread_t*)malloc(sizeof(pthread_t) * (count + 1))))
		print_error("Sorry, memory allocation error((");
	return (0);
}
