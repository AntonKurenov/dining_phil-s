/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:24:55 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/28 15:36:50 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		print_state(int type, t_phil *phil)
{
	size_t	now;

	now = ft_gettime();
	usleep(20);
	if (*phil->someone_died)
		return ;
	pthread_mutex_lock(phil->print);
	if (type == 1)
		printf("%zu %d has taken a fork\n", now - phil->start_time, phil->num);
	if (type == 2)
		printf("%zu %d is eating\n", now - phil->start_time, phil->num);
	if (type == 3)
		printf("%zu %d is sleeping\n", now - phil->start_time, phil->num);
	if (type == 4)
		printf("%zu %d is thinking\n", now - phil->start_time, phil->num);
	pthread_mutex_unlock(phil->print);
}

void		take_forks(t_phil *phil)
{
	if (*phil->someone_died)
		return ;
	if ((phil->num & 0x1) == 0)
	{
		pthread_mutex_lock(phil->left_fork);
		print_state(1, phil);
		pthread_mutex_lock(phil->right_fork);
		print_state(1, phil);
	}
	else
	{
		pthread_mutex_lock(phil->right_fork);
		print_state(1, phil);
		if (phil->ph_num == 1)
		{
			ft_sleep(phil->tt_die + 2);
			return ;
		}
		pthread_mutex_lock(phil->left_fork);
		print_state(1, phil);
	}
	phil->last_eat = ft_gettime();
	print_state(2, phil);
	ft_sleep(phil->tt_eat);
}

void		ft_end(t_phil *phil)
{
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
}

void *new_print_dead(t_phil *phil, size_t now, int i)
{
	*phil->someone_died = 1;
	pthread_mutex_lock(phil->print);
	printf("%zu %d died\n", now - phil->start_time, i);
	ft_sleep(30);
	pthread_mutex_unlock(phil->print);
	return (0);
}

void		*observ_2(void *data)
{
	t_phil *phil;
	size_t now;
	int		is_dead;

	phil = (t_phil*)data;
	is_dead = 0;
	printf("hello\n");
	while (!is_dead)
	{
		now = ft_gettime();
		if (now - phil->last_eat > phil->tt_die)
		{
			if (*phil->finished == phil->ph_num)
				return (0);
			// if (phil->ended == 1 && *phil->finished == phil->ph_num)
			// 	return (0);
			if (*phil->someone_died == 1)
				return (0);
			*phil->someone_died = 1;
			return (new_print_dead(phil, now, phil->num));
		}
		if (phil->ended == 1)
			return (0);
		ft_sleep(1);
	}
	return (0);
}

void		*simulation(void *data)
{
	t_phil	*phil;
	pthread_t obs;

	phil = (t_phil*)data;
	phil->last_eat = phil->start_time;
	if (pthread_create(&obs, NULL, observ_2, (void*)phil))
		print_error("Failed to create thread!");
	pthread_detach(obs);
	while (1)
	{
		if (phil->eat_count == 0)
			break ;
		take_forks(phil);
		if (phil->eat_count != -1)
			phil->eat_count--;
		pthread_mutex_unlock(phil->right_fork);
		pthread_mutex_unlock(phil->left_fork);
		if (*phil->someone_died)
			break ;
		print_state(3, phil);
		ft_sleep(phil->tt_sleep);
		print_state(4, phil);
		if (phil->eat_count == 0)
			break ;
	}
	ft_end(phil);
	*phil->finished += 1;
	phil->ended = 1;
	return (0);
}
