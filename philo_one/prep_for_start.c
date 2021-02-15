/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:37:50 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/15 14:33:43 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_each_phil(t_main *data, t_phil *phil, int i)
{
	phil->data = data;
	phil->print = data->print;
	phil->num = i;
	phil->eat_count = data->eat_count;
	printf("i = %d\n", phil->num);
	if (i == data->ph_num)
	{
		phil->left_fork = data->forks + data->ph_num;
		phil->right_fork = data->forks;
	}
	else
	{
		phil->left_fork = data->forks + i;
		phil->right_fork = data->forks + i + 1;
	}
	if (pthread_mutex_init(phil->left_fork, NULL) || pthread_mutex_init(phil-> \
		right_fork, NULL))
		ft_error("Failed to initialize mutex\n");
}

int preparation(t_main *data)
{
	int i;

	i = -1;
	if (!(data->arr_phil = (t_phil *)malloc(sizeof(t_phil) * data->ph_num)))
		ft_error("Sorry, memory allocation error((\n");
	if (!(data->forks = (mutex_t *)malloc(sizeof(mutex_t) * data->ph_num)))
		ft_error("Sorry, memory allocation error((\n");
	if (!(data->print = (mutex_t *)malloc(sizeof(mutex_t))))
		ft_error("Sorry, memory allocation error((\n");
	while (++i < data->ph_num)
	{
		fill_each_phil(data, &data->arr_phil[i], i);
	}
	printf("ph_num = %d\n", data->ph_num);
	data->phil_thr = (pthread_t *)malloc(sizeof(pthread_t) * (data->ph_num + 1));
	data->observer = data->phil_thr + data->ph_num;
	return (0);
}
