/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:20:45 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/19 15:21:44 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int check_input(int argc, char **argv, t_main *data)
{
	data->eat_count = (argc == 5) ? -1 : ft_atoi(argv[5]);
	if ((data->ph_num = ft_atoi(argv[1])) == -1)
		print_error("Error: Invalid input");
	if ((data->tt_die = ft_atoi(argv[2])) == -1)
		print_error("Error: Invalid input");
	if ((data->tt_eat = ft_atoi(argv[3])) == -1)
		print_error("Error: Invalid input");
	if ((data->tt_sleep = ft_atoi(argv[4])) == -1)
		print_error("Error: Invalid input");
	return (0);
}

int main(int argc, char **argv)
{
	t_main data;

	if (argc < 5 || argc > 6)
		print_error("Error: Invalid input");
	check_input(argc, argv, &data);
	preparation(&data);
	start_threads(&data);
	free(data.arr_phil);
	free(data.forks);
	free(data.print);
	return (0);
}
