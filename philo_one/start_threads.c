/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:36:58 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/09 14:03:27 by elovegoo         ###   ########.fr       */
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
			pthread_create(data->phil_thr, NULL, &simulation, (void*)data->\
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
			pthread_create(data->phil_thr, NULL, &simulation, (void*)data->\
				arr_phil[i]);
	}
	i = -1;
	while (++i < data->ph_num)
	{
		if (i % 2 != 0)
			pthread_detach(data->phil_thr[i]);
	}
}

int start(t_main *data)
{
	start_even(data);
	start_odd(data);

	return (0);
}
