/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:36:58 by elovegoo          #+#    #+#             */
/*   Updated: 2021/03/03 16:28:02 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static	void	print_dead(t_main *data, size_t now, int i)
{
	data->someone_died = 1;
	pthread_mutex_lock(data->print);
	printf("%zu %d died\n", now - data->arr_phil[i].start_time,\
			data->arr_phil[i].num);
}

static	void	observation(t_main *data)
{
	size_t		now;
	int			i;

	while (1)
	{
		i = 0;
		while (++i <= data->ph_num)
		{
			now = ft_gettime();
			if (now - data->arr_phil[i].last_eat > data->tt_die && \
				data->arr_phil[i].ended != 1)
				return (print_dead(data, now, i));
			if (data->finished == data->ph_num)
			{
				pthread_mutex_lock(data->print);
				return ;
			}
		}
		ft_sleep(1);
	}
}

int				start_threads(t_main *data)
{
	int			i;

	data->someone_died = 0;
	data->finished = 0;
	i = 0;
	while (++i <= data->ph_num)
	{
		if (pthread_create(data->phil_thr + i, NULL, simulation, (void*)(data->\
			arr_phil + i)))
			print_error("Failed to create thread!");
		usleep(10);
	}
	ft_sleep(2);
	i = 0;
	while (++i <= data->ph_num)
		pthread_detach(data->phil_thr[i]);
	observation(data);
	return (0);
}
