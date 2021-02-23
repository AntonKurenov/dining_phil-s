/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:33:33 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/23 19:34:17 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			print_state(int type, t_phil *phil)
{
	size_t		now;

	now = ft_gettime();
	if (*phil->someone_died)
		return ;
	sem_wait(phil->print);
	if (type == 1)
		printf("%zu %d has taken a fork\n", now - phil->start_time, phil->num);
	if (type == 2)
		printf("%zu %d is eating\n", now - phil->start_time, phil->num);
	if (type == 3)
		printf("%zu %d is sleeping\n", now - phil->start_time, phil->num);
	if (type == 4)
		printf("%zu %d is thinking\n", now - phil->start_time, phil->num);
	sem_post(phil->print);
}

void			waiter(t_phil *phil)
{
	if (*phil->someone_died)
		return ;
	sem_wait(phil->waiter);
	sem_wait(phil->forks);
	print_state(1, phil);
	if (phil->ph_num == 1)
	{
		ft_sleep(phil->tt_die + 2);
		return ;
	}
	sem_wait(phil->forks);
	print_state(1, phil);
	sem_post(phil->waiter);
	print_state(2, phil);
	phil->last_eat = ft_gettime();
	ft_sleep(phil->tt_eat);
	sem_post(phil->forks);
	sem_post(phil->forks);
}

void			*observation(void *info)
{
	size_t		now;
	t_phil		*phil;

	phil = (t_phil*)info;
	while (1)
	{
		now = ft_gettime();
		if (*phil->someone_died == 1)
			return (0);
		if (now - phil->last_eat > phil->tt_die)
		{
			*phil->someone_died = 1;
			sem_wait(phil->print);
			printf("%zu %d died\n", now - phil->start_time, phil->num);
			return (0);
		}
		if (*phil->someone_died == 1)
			return (0);
		ft_sleep(1);
	}
}

void			*simulation(void *data)
{
	t_phil		*phil;
	pthread_t	obs;

	phil = (t_phil*)data;
	phil->start_time = ft_gettime();
	phil->last_eat = phil->start_time;
	if (pthread_create(&obs, NULL, observation, data))
		print_error("Error: pthread_create function failed");
	pthread_detach(obs);
	while (1)
	{
		if (*phil->someone_died)
			exit(1);
		if (phil->eat_count == 0)
			exit(0);
		if (phil->eat_count != -1)
			phil->eat_count--;
		waiter(phil);
		print_state(3, phil);
		if (*phil->someone_died)
			exit(1);
		ft_sleep(phil->tt_sleep);
		print_state(4, phil);
	}
	exit(0);
}
