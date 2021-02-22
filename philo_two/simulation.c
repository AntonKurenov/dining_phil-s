/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:33:33 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/17 13:3 by1 elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	print_state(int type, t_phil *phil)
{
	size_t now;

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

void waiter(t_phil *phil)
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
	ft_sleep(phil->tt_eat);
	phil->last_eat = ft_gettime();
	sem_post(phil->forks);
	sem_post(phil->forks);
}

void *simulation(void *data)
{
	t_phil *phil;

	phil = (t_phil*)data;
	phil->start_time = ft_gettime();
	phil->last_eat = phil->start_time;
	while (1)
	{
		if (*phil->someone_died)
			break ;
		if (phil->eat_count == 0)
			break ;
		if (phil->eat_count != -1)
			phil->eat_count--;
		waiter(phil);
		if (*phil->someone_died)
			break ;
		print_state(3, phil);
		if (*phil->someone_died)
			break ;
		ft_sleep(phil->tt_sleep);
		print_state(4, phil);
	}
	return (0);
}
