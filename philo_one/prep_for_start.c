/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:37:50 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/09 12:10:59 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void give_forks(t_phil *phil, int i)
{
	int num;

	if (i % 2 == 1)
	{
		phil->left_fork = i;
		if (i == 1)
			phil->right_fork = phil->data->ph_num;
		else
			phil->right_fork = i - 1;
	}
	else
	{
		phil->left_fork = i;
		phil->right_fork = i - 1;
	}
}

int init_arr_phil(t_main *data, int i)
{
	if (!(data->arr_phil[i] = (t_phil *)malloc(sizeof(t_phil))))
	{
		ft_error("Sorry, memory allocation error(\n");
		return (1);
	}
	data->arr_phil[i]->ph_num = i;
	data->arr_phil[i]->data = data;
	data->arr_phil[i]->eat_count = data->eat_count;
	// data->arr_phil[i]->
	give_forks(data->arr_phil[i], i + 1);
	if (pthread_mutex_init(&data->forks[i], NULL))
	{
		ft_error("Can't initialize mutex\n");
		return(1);
	}
	return (0);
}

int preparation(t_main *data)
{
	int i;

	// memory allocation block
	data->phil_thr = (pthread_t *)malloc(sizeof(pthread_t) * data->ph_num);
	data->arr_phil = (t_phil **)malloc(sizeof(t_phil *) * data->ph_num);
	data->forks = (mutex_t *)malloc(sizeof(mutex_t) * data->ph_num);
	i = -1;
	while (++i < data->ph_num)
	{
		if (init_arr_phil(data, i))
			return (1);
	}
	return (0);

}
