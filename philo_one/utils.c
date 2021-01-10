/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elovegoo <elovegoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:20:41 by elovegoo          #+#    #+#             */
/*   Updated: 2021/01/10 12:21:44 by elovegoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return(i);
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
