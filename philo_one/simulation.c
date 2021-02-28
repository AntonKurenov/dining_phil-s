/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:33:33 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/28 20:31:11 by elovegoo         ###   ########.fr       */
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

void		*simulation(void *data)
{
	t_phil	*phil;

	phil = (t_phil*)data;
	phil->last_eat = phil->start_time;
	while (1)
	{
		if (phil->eat_count == 0)
			ft_sleep(phil->tt_die);
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
			ft_sleep(phil->tt_die);
	}
	ft_end(phil);
	// *phil->finished += 1;
	phil->ended = 1;
	return (0);
}
