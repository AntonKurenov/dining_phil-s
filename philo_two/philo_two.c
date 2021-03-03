/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:20:45 by elovegoo          #+#    #+#             */
/*   Updated: 2021/03/03 16:36:24 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static	int		check_input(int argc, char **argv, t_main *data)
{
	if (argc == 6)
	{
		if ((data->eat_count = ft_atoi(argv[5])) == -1)
			print_error("Error: Invalid input");
	}
	if (data->eat_count == 0)
		print_error("Error: Invalid input");
	if ((data->ph_num = ft_atoi(argv[1])) == -1)
		print_error("Error: Invalid input");
	if (data->ph_num == 0)
		print_error("Error: Invalid input");
	if ((data->tt_die = ft_atoi(argv[2])) == -1)
		print_error("Error: Invalid input");
	if ((data->tt_eat = ft_atoi(argv[3])) == -1)
		print_error("Error: Invalid input");
	if ((data->tt_sleep = ft_atoi(argv[4])) == -1)
		print_error("Error: Invalid input");
	return (0);
}

int				main(int argc, char **argv)
{
	t_main		data;

	if (argc < 5 || argc > 6)
		print_error("Error: Invalid input");
	check_input(argc, argv, &data);
	sem_unlink("forks");
	sem_unlink("waiter");
	sem_unlink("print");
	preparation(&data);
	start_threads(&data);
	sem_unlink("forks");
	sem_unlink("waiter");
	sem_unlink("print");
	free(data.arr_phil);
	free(data.phil_thr);
	return (0);
}
