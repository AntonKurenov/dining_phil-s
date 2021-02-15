/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:36:58 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/15 12:22:42 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *observation(void *info)
{
	t_main *data;
	int i;
	// long int tt_die;

	data = (t_main*)info;
	i = -1;
	printf("|||||||||\n");
	while (1)
	{
		while (++i < data->ph_num)
		{
			if (data->arr_phil[i].last_eat > data->tt_die)
			{
				print_state(5, data->arr_phil + i);
				exit(1);
				// ft_stop();
			}
		}
		ft_sleep(50);
	}
}

int start_threads(t_main *data)
{
	int i;

	i = -1;
	while (++i < data->ph_num)
	{
		printf("i = %d\n", i);
		if (pthread_create(data->phil_thr + i, NULL, &simulation, (void*)(data->\
			arr_phil + i)))
			ft_error("Failed to create thread!\n");
	}
	if (pthread_create(data->observer, NULL, &observation, (void*)data))
			ft_error("Failed to create thread!\n");
	return (0);	
}
