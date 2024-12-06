/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihaffout <ihaffout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:59:46 by ihaffout          #+#    #+#             */
/*   Updated: 2024/06/24 14:40:15 by ihaffout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error(char *str)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "Error: ", 7);
	while (str[i])
	{
		write(STDERR_FILENO, &str[i], 1);
		i++;
	}
	write(STDERR_FILENO, ".\n", 2);
	return (1);
}

int	ft_detach(int option, int index, t_parameters *params,
		t_philosopher *philosophers)
{
	int	i;

	i = 0;
	if (option == 1)
	{
		i = index - 2;
		while (i >= 0)
		{
			pthread_detach(philosophers[i].thread);
			i -= 2;
		}
	}
	else if (option == 2)
	{
		i = index + 1;
		while (i < params->num_philo)
		{
			pthread_detach(philosophers[i].thread);
			i += 2;
		}
		i = index - 1;
		while (i >= 0)
			pthread_detach(philosophers[index--].thread);
	}
	return (1);
}
