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

#include "philo.h"

void *observation(void *info)
{
	t_main *data;
	int i;
	size_t now;
	int flag;

	data = (t_main*)info;
	printf("|||||||||\n");
	while (1)
	{
		i = 0;
		while (++i < data->ph_num)
		{
			now = ft_gettime();
			flag = 0;
			if (data->arr_phil[i].eat_count == 0)
				flag++;
			else if (now - data->arr_phil[i].last_eat > data->tt_die && data->\
				arr_phil[i].eat_count != 0)
			{
				data->someone_died = 1;
				pthread_mutex_lock(data->print);
				printf("%zu %d died\n", now - data->arr_phil[i].start_time,\
					data->arr_phil[i].num);
				// exit(3);
				return 0;
			}
			if (flag == data->ph_num)
			{
				printf("inside if\n");
				return 0;
			}
		}
		ft_sleep(3);
	}
}

int start_threads(t_main *data)
{
	int i;

	i = 0;
	data->someone_died = 0;
	while (++i <= data->ph_num)
	{
		printf("i = %d\n", i);
		if (pthread_create(data->phil_thr + i, NULL, simulation, (void*)(data->\
			arr_phil + i)))
			ft_error("Failed to create thread!\n");
	}
	ft_sleep(50);
	if (pthread_create(data->observer, NULL, observation, (void*)data))
			ft_error("Failed to create thread!\n");
	i = 0;
	while (++i <= data->ph_num)
	{
		pthread_join(data->phil_thr[i], NULL);
	}
	pthread_join(data->observer[0], NULL);
	return (0);	
}
