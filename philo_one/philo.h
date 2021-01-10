/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:28:57 by elovegoo          #+#    #+#             */
/*   Updated: 2021/01/10 12:11:45 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef pthread_mutex_t t_mutex;

typedef struct s_data
{
	int 	ph_num;
	int 	tt_die;
	int 	tt_eat;
	int 	tt_sleep;
	int 	eat_count;
}			t_data;

int			ft_atoi(char *str);
int			print_error(int error);

#endif
