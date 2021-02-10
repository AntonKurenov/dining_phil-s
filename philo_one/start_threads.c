/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:36:58 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/10 11:48:12 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_even(t_main *data)
{
	int i;

	i = -1;
	while (++i < data->ph_num)
	{
		if (i % 2 == 0)
			pthread_create(data->phil_thr + i, NULL, &simulation, (void*)data->\
				arr_phil[i]);
	}
	i = -1;
	while (++i < data->ph_num)
	{
		if (i % 2 == 0)
			pthread_detach(data->phil_thr[i]);
	}
}

void start_odd(t_main *data)
{
	int i;

	i = -1;
	while (++i < data->ph_num)
	{
		if (i % 2 != 0)
			pthread_create(data->phil_thr + i, NULL, &simulation, (void*)data->\
				arr_phil[i]);
	}
	i = -1;
	while (++i < data->ph_num)
	{
		if (i % 2 != 0)
			pthread_detach(data->phil_thr[i]);
	}
}

void *test_func(void *data)
{
	t_phil *phil;
	char str[] = "Hello from thread!\n";

	phil = (t_phil*)data;
	printf("%s", str);
	if (phil->num == 1)
	{
		// usleep(100);
		printf("I'm second thread\n");
	}
}

void	start_all(t_main *data)
{
	int i = 0;

	while (i < data->ph_num)
	{
		pthread_create(&data->phil_thr[i], NULL, &test_func, (void*)data->\
			arr_phil[i]);
		i++;
	}
	i = 0;
	while (i < data->ph_num)
	{
		pthread_detach(data->phil_thr[i]);
		i++;
	}
}

int start(t_main *data)
{
	// start_all(data);
	start_even(data);
	start_odd(data);

	return (0);
}
