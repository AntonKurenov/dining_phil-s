/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:33:33 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/16 19:17:03 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(int type, t_phil *phil)
{
	long int now;

	now = ft_gettime();
	if (phil->data->someone_died)
		return ;
	pthread_mutex_lock(phil->print);
	// printf("start_time = %zu now = %zu\n", phil->start_time, now);
	if (type == 1)
		printf("%zu %d has taken a fork\n", now - phil->start_time, phil->num);
	if (type == 2)
		printf("%zu %d is eating\n", now - phil->start_time, phil->num);
	if (type == 3)
		printf("%zu %d is sleeping\n", now - phil->start_time, phil->num);
	if (type == 4)
		printf("%zu %d is thinking\n", now - phil->start_time, phil->num);
	if (type == 5)
		printf("%zu %d died\n", now - phil->start_time, phil->num);
	pthread_mutex_unlock(phil->print);
}

void take_forks(t_phil *phil)
{
	// printf("Hello there\n");
	// printf("inside take forks num = %d\n", phil->num);
	if (phil->data->someone_died)
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
		pthread_mutex_lock(phil->left_fork);
		print_state(1, phil);
	}
}

void ft_end(t_phil *phil)
{
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
}

void *simulation(void *data)
{
	t_phil *phil;
	int i;
	int j;

	phil = (t_phil*)data;
	phil->start_time = ft_gettime();
	// printf("time is = %zu\n", phil->start_time);
	// printf("phil_num = %d\n", phil->num);
	printf("eat_count = %d\n", phil->eat_count);
	phil->last_eat = phil->start_time;
	while (1)
	{
		if (phil->eat_count == 0)
		{
			printf(".....inside if philo->num == %d\n", phil->num);
			break ;
		}
		if (phil->eat_count != -1)
			phil->eat_count--;
		take_forks(phil);
		if (phil->data->someone_died)
			break ;
		print_state(2, phil);
		phil->last_eat = ft_gettime();
		ft_sleep(phil->tt_eat);
		// printf("after sleep_eat phil = %d\n", phil->num);
		phil->last_eat = ft_gettime();
		pthread_mutex_unlock(phil->right_fork);
		pthread_mutex_unlock(phil->left_fork);
		// printf("after sleep_eat phil = %d\n", phil->num);
		if (phil->data->someone_died)
			break ;
		print_state(3, phil);
		ft_sleep(phil->tt_sleep);
		if (phil->data->someone_died)
			break ;
		print_state(4, phil);
	}
	// printf("after while\n");
	ft_end(phil);
	return (0);
}
