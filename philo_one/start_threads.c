/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:36:58 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/15 17:30:47 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *observation(void *info)
{
	t_main *data;
	int i;
	long int current_time;

	data = (t_main*)info;
	i = -1;
	printf("|||||||||\n");
	while (1)
	{
		while (++i < data->ph_num)
		{
			current_time = ft_gettime();
			if (current_time - data->arr_phil[i].last_eat > data->tt_die)
			{
				data->someone_died = 1;
				pthread_mutex_lock(data->print);
				printf("%zu %d died\n", current_time - data->arr_phil[i].start_time,\
					data->arr_phil[i].num);
				exit(1);
				// ft_stop();
			}
		}
		ft_sleep(5);
	}
}

// void end_all(t_main *data)
// {
// 	int i;

	

int start_threads(t_main *data)
{
	int i;

	i = -1;
	data->someone_died = 0;
	while (++i < data->ph_num)
	{
		printf("i = %d\n", i);
		if (pthread_create(data->phil_thr + i, NULL, &simulation, (void*)(data->\
			arr_phil + i)))
			ft_error("Failed to create thread!\n");
	}
	if (pthread_create(data->observer, NULL, &observation, (void*)data))
			ft_error("Failed to create thread!\n");
	// end_all(data);
	i = -1;
	while (++i < data->ph_num)
	{
		pthread_join(data->phil_thr[i], NULL);
	}
	pthread_join(data->observer[0], NULL);
	return (0);	
}
