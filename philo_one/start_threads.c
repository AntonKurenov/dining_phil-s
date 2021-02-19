/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:36:58 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/16 10:33:1 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*print_dead(t_main *data, size_t now, int i)
{
	data->someone_died = 1;
	pthread_mutex_lock(data->print);
	printf("%zu %d died\n", now - data->arr_phil[i].start_time,\
			data->arr_phil[i].num);
	return (0);
}

void *observation(void *info)
{
	t_main *data;
	int i;
	size_t now;
	int flag;

	data = (t_main*)info;
	while (1)
	{
		i = 0;
		flag = 0;
		while (++i <= data->ph_num)
		{
			now = ft_gettime();
			if (data->arr_phil[i].eat_count == 0)
				flag++;
			if (flag == data->ph_num)
				return 0;
			else if (now - data->arr_phil[i].last_eat > data->tt_die && data->\
				arr_phil[i].eat_count != 0)
				return (print_dead(data, now, i));
		}
		ft_sleep(1);
	}
}

int start_threads(t_main *data)
{
	int i;

	i = 0;
	data->someone_died = 0;
	while (++i <= data->ph_num)
	{
		if (pthread_create(data->phil_thr + i, NULL, simulation, (void*)(data->\
			arr_phil + i)))
			print_error("Failed to create thread!");
	}
	ft_sleep(50);
	if (pthread_create(data->observer, NULL, observation, (void*)data))
			print_error("Failed to create thread!");
	i = 0;
	while (++i <= data->ph_num)
	{
		pthread_join(data->phil_thr[i], NULL);
	} 
	pthread_join(data->observer[0], NULL); return (0);
}
