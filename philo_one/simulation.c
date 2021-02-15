/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:33:33 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/15 17:02:02 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(int type, t_phil *phil)
{
	long int now = ft_gettime();

	pthread_mutex_lock(phil->print);
	printf("start_time = %zu now = %zu\n", phil->start_time, now);
	if (type == 1)
		printf("%zu %d has taken a fork\n", ft_gettime() - phil->start_time, phil->num);
	if (type == 2)
		printf("%zu %d is eating\n", ft_gettime() - phil->start_time, phil->num);
	if (type == 3)
		printf("%zu %d is sleeping\n", ft_gettime() - phil->start_time, phil->num);
	if (type == 4)
		printf("%zu %d is thinking\n", ft_gettime() - phil->start_time, phil->num);
	if (type == 5)
		printf("%zu %d died\n", ft_gettime() - phil->start_time, phil->num);
	pthread_mutex_unlock(phil->print);
}

void take_forks(t_phil *phil)
{
	printf("Hello there\n");
	printf("inside take forks num = %d\n", phil->num);
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

void *simulation(void *data)
{
	t_phil *phil;
	int i;
	int j;

	phil = (t_phil*)data;
	phil->start_time = ft_gettime();
	// printf("start_time = %ld\n", phil->start_time);
	// phil->start_life = ft_gettime();
	printf("time is = %zu\n", phil->start_time);
	printf("phil_num = %d\n", phil->num);
	phil->last_eat = phil->start_time;
	// sleep(1);
	// printf("time is = %zu\n", phil->start_time);
	// while (1)
	while (phil->data->someone_died != 1)
	{
		take_forks(phil);
		print_state(2, phil);
		phil->last_eat = ft_gettime();
		ft_sleep(phil->tt_eat);
		// if (phil->eat_count != -1)
		// 	phil->eat_count--;
		// if (phil->eat_count == 0)
		// 	break ;
		pthread_mutex_unlock(phil->right_fork);
		pthread_mutex_unlock(phil->left_fork);
		print_state(3, phil);
		ft_sleep(phil->tt_sleep);
		print_state(4, phil);
	}
}
