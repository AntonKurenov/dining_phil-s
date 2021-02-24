/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:20:45 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/24 12:23:17 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			check_input(int argc, char **argv, t_main *data)
{
	data->eat_count = (argc == 5) ? -1 : ft_atoi(argv[5]);
	if ((data->ph_num = ft_atoi(argv[1])) == -1)
		print_error("Error: Invalid input");
	if (data->ph_num < 1)
		print_error("Error: Invalid input");
	if ((data->tt_die = ft_atoi(argv[2])) == -1)
		print_error("Error: Invalid input");
	if ((data->tt_eat = ft_atoi(argv[3])) == -1)
		print_error("Error: Invalid input");
	if ((data->tt_sleep = ft_atoi(argv[4])) == -1)
		print_error("Error: Invalid input");
	return (0);
}

void		ft_free(t_main *data)
{
	sem_post(data->print);
	if (sem_close(data->forks) != 0)
		print_error("Error: sem_close returned an error");
	if (sem_close(data->waiter) != 0)
		print_error("Error: sem_close returned an error");
	if (sem_close(data->print) != 0)
		print_error("Error: sem_close returned an error");
	sem_unlink("forks");
	sem_unlink("waiter");
	sem_unlink("print");
	free(data->arr_phil);
	free(data->pids);
}

int			main(int argc, char **argv)
{
	t_main	data;

	if (argc < 5 || argc > 6)
		print_error("Error: Invalid input");
	check_input(argc, argv, &data);
	sem_unlink("forks");
	sem_unlink("waiter");
	sem_unlink("print");
	preparation(&data);
	ft_free(&data);
	return (0);
}
