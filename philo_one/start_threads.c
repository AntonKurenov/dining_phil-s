/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:36:58 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/28 20:14:07 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		*print_dead(t_main *data, size_t now, int i)
{
	data->someone_died = 1;
	pthread_mutex_lock(data->print);
	printf("%zu %d died\n", now - data->arr_phil[i].start_time,\
			data->arr_phil[i].num);
	ft_sleep(10);
	pthread_mutex_unlock(data->print);
	return (0);
}

void		*observ_eat(void *info)
{
	t_main	*data;
	int		i;
	int		count;

	printf("inside eat_observ\n");
	data = (t_main*)info;
	while (1)
	{
		i = 1;
		count = 0;
		while (i <= data->ph_num)
		{
			if (data->arr_phil[i].eat_count == 0)
				count++;
			i++;
		}
		if (count == data->ph_num)
		{
			data->someone_died = 1;
			printf("count = %d\n", count);
			if (data->someone_died)
				return (0);
			pthread_mutex_lock(data->print);
			return (0);
		}
		usleep(50);
	}
}

void		*observation(void *info)
{
	t_main	*data;
	size_t	now;
	int		i;
	int		count;

	printf("inside observation\n");
	data = (t_main*)info;
	while (1)
	{
		i = 0;
		count = 0;
		while (++i <= data->ph_num)
		{
			if (data->arr_phil[i].eat_count == 0)
				count++;
		}
		if (count == data->ph_num)
		{
			data->someone_died = 1;
			printf("count = %d\n", count);
			if (data->someone_died)
				return (0);
			pthread_mutex_lock(data->print);
			return (0);
		}
		i = 0;
		while (++i <= data->ph_num)
		{
			now = ft_gettime();
			if (data->someone_died)
				return (0);
			if (now - data->arr_phil[i].last_eat > data->tt_die)
			{
				if (data->someone_died)
					return (0);
				return (print_dead(data, now, i));
			}
			if (data->someone_died)
				return (0);
		}
		ft_sleep(1);
	}
}

void		next_start_threads(t_main *data)
{
	int		i;

	i = 0;
	while (++i <= data->ph_num)
	{
		if (pthread_create(data->phil_thr + i, NULL, simulation, (void*)(data->\
			arr_phil + i)))
			print_error("Failed to create thread!");
	}
	// if (data->eat_count != -1)
	// {
	// 	if (pthread_create(data->eat_observ, NULL, observ_eat, (void*)data))
	// 		print_error("Failed to create thread!");
	// }
	ft_sleep(5);
	if (pthread_create(data->observer, NULL, observation, (void*)data))
		print_error("Failed to create thread!");
}

int			start_threads(t_main *data)
{
	int		i;

	data->someone_died = 0;
	data->finished = 0;
	next_start_threads(data);
	i = 0;
	while (++i <= data->ph_num)
	{
		pthread_join(data->phil_thr[i], NULL);
	}
	pthread_join(data->observer[0], NULL);
	// if (data->eat_count != -1)
	// 	pthread_join(*data->eat_observ, NULL);
	return (0);
}
