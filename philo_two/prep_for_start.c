/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:37:50 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/23 17:38:38 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	fill_each_phil(t_main *data, t_phil *phil, int i)
{
	phil->someone_died = &data->someone_died;
	phil->finished = &data->finished;
	phil->forks = data->forks;
	phil->waiter = data->waiter;
	phil->print = data->print;
	phil->num = i;
	phil->eat_count = data->eat_count;
	phil->tt_eat = data->tt_eat;
	phil->tt_sleep = data->tt_sleep;
	phil->tt_die = data->tt_die;
	phil->ph_num = data->ph_num;
}

int		preparation(t_main *data)
{
	int	i;
	int	ph_count;

	i = -1;
	ph_count = data->ph_num;
	if (!(data->arr_phil = (t_phil *)malloc(sizeof(t_phil) * (ph_count))))
		print_error("Sorry, memory allocation error((");
	if (!(data->forks = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU, ph_count)))
		print_error("Error, sem_open function failed((");
	if (!(data->waiter = sem_open("waiter", O_CREAT | O_EXCL, S_IRWXU, 1)))
		print_error("Error, sem_open function failed((");
	if (!(data->print = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1)))
		print_error("Error, sem_open function failed((");
	while (++i < data->ph_num)
		fill_each_phil(data, data->arr_phil + i, i + 1);
	if (!(data->phil_thr = (pthread_t *)malloc(sizeof(pthread_t) * \
			(ph_count + 1))))
		print_error("Sorry, memory allocation error((");
	data->observer = data->phil_thr + data->ph_num;
	return (0);
}
