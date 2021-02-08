/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:33:33 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/08 19:23:26 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_forks(t_phil *phil)
{
	printf("Hello there\n");
	
}

void simulation(void *data)
{
	t_phil *phil;
	int i;
	int j;

	phil = (t_phil*)data;
	phil->start_time = ft_gettime();
	phil->start_life = ft_gettime();
	take_forks(phil);
	// while (1)
	// {
	// 	take_forks(phil);
	sleep(5);
}
