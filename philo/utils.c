/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihaffout <ihaffout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:01:31 by ihaffout          #+#    #+#             */
/*   Updated: 2024/06/23 20:37:34 by ihaffout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		else
			result = result * 10 + (str[i++] - '0');
	}
	if (result > INT_MAX)
		return (-1);
	return (result);
}
