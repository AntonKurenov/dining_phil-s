/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 10:37:50 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/22 16:30:18 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	fill_each_phil(t_main *data, t_phil *phil, int i)
{
	phil->ph_num = data->ph_num;
	phil->someone_died = &data->someone_died;
	phil->forks = data->forks;
	phil->waiter = data->waiter;
	phil->print = data->print;
	phil->num = i + 1;
	phil->eat_count = data->eat_count;
	phil->tt_eat = data->tt_eat;
	phil->tt_sleep = data->tt_sleep;
	phil->tt_die = data->tt_die;
}

static void	open_semaphors(t_main *data)
{
	int		ph_count;

	ph_count = data->ph_num;
	if (!(data->forks = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU, ph_count)))
		print_error("Error: sem_open function failed((");
	if (!(data->waiter = sem_open("waiter", O_CREAT | O_EXCL, S_IRWXU, 1)))
		print_error("Error: sem_open function failed((");
	if (!(data->print = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1)))
		print_error("Error: sem_open function failed((");
}

static void	wait_or_kill(t_main *data)
{
	int		i;
	int		status;
	int		finished;

	i = -1;
	status = 0;
	finished = 0;
	while (status == 0 && finished < data->ph_num)
	{
		if (waitpid(-1, &status, 0) < 0)
			printf("Error: waitpid failed\n");
		finished++;
	}
	if (status != 0)
	{
		while (++i < data->ph_num)
			kill(data->pids[i], SIGTERM);
	}
}

int			preparation(t_main *data)
{
	int		i;
	int		ph_count;
	int		status;
	int		finished;

	i = -1;
	ph_count = data->ph_num;
	data->someone_died = 0;
	if (!(data->arr_phil = (t_phil *)malloc(sizeof(t_phil) * (ph_count))))
		print_error("Sorry, memory allocation error((");
	if (!(data->pids = (pid_t *)malloc(sizeof(pid_t) * ph_count)))
		print_error("Sorry, memory allocation error((");
	open_semaphors(data);
	while (++i < ph_count)
	{
		fill_each_phil(data, data->arr_phil + i, i);
		if ((data->pids[i] = fork()) == 0)
			simulation((void*)(data->arr_phil + i));
		if (data->pids[i] == -1)
			print_error("Error: fork function failed");
	}
	wait_or_kill(data);
	return (0);
}
