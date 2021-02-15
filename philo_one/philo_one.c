/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:20:45 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/15 12:26:42 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_input(int argc, char **argv, t_main *data)
{
	int i;

	if ((data->ph_num = ft_atoi(argv[1])) == -1)
		return (print_error(1));
	if ((data->tt_die = ft_atoi(argv[2])) == -1)
		return (print_error(1));
	if ((data->tt_eat = ft_atoi(argv[3])) == -1)
		return (print_error(1));
	if ((data->tt_sleep = ft_atoi(argv[4])) == -1)
		return (print_error(1));
	if (argc == 6)
	{
		if ((data->eat_count = ft_atoi(argv[5])) == -1)
			return (print_error(1));
	}
	return (0);
}

int main(int argc, char **argv)
{
	int i;
	int j;
	t_main data;

	if (argc < 5 || argc > 6)
		return (print_error(1));
	else if (check_input(argc, argv, &data) == 1)
		return (0);
	preparation(&data);
	start_threads(&data);
	// check_struct();
	// start_simulation(data);
	// usleep(100);
	sleep(5);
	return (0);
}
