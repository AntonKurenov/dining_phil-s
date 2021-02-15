/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:20:41 by elovegoo          #+#    #+#             */
/*   Updated: 2021/02/15 12:13:16 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void ft_stop(void)
// {


size_t		ft_gettime(void)
{
	t_time tm;

	gettimeofday(&tm, NULL);
	return((size_t)tm.tv_sec * 1000 + (size_t)tm.tv_usec / 1000);
}

void	ft_sleep(int time)
{
	size_t start;
	size_t now_time;

	start = ft_gettime();
	while (1)
	{
		now_time = ft_gettime();
		if (now_time - start >= time)
			break ;
		usleep(100);
	}
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

void ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

int print_error(int error)
{
	if (error == 1)
	{
		write(1, "Invalid input\n", ft_strlen("Invalid input\n"));
		return (1);
	}
	return (0);
}

int			ft_atoi(char *str)
{
	unsigned int	ret;
	int i;

	ret = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+' || str[i] <= '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (ret);
}
