/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihaffout <ihaffout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:18:52 by ihaffout          #+#    #+#             */
/*   Updated: 2024/06/25 15:56:13 by ihaffout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_full(t_philosopher *philosopher)
{
	if ((philosopher->meals_eaten >= philosopher->params->eat_limit)
		&& philosopher->params->eat_limit != -1)
		philosopher->full = 1;
	return ;
}

int	check_limit(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	while (i < philosopher->params->num_philo)
	{
		if ((&philosopher[i])->full != 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_dead(t_philosopher *philosopher)
{
	if (current_time()
		- philosopher->last_meal_time > philosopher->params->time_die)
		return (1);
	return (0);
}

int	death_checker(t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philosophers->params->mutex);
		check_full(&philosophers[i]);
		if (check_limit(philosophers) == 0)
			break ;
		if (check_dead(&philosophers[i]))
		{
			pthread_mutex_lock(&(philosophers->params->write));
			printf("%lld %d died\n", (current_time()
					- philosophers->params->start_simulation),
				philosophers[i].id);
			return (1);
		}
		i = (i + 1) % philosophers->params->num_philo;
		pthread_mutex_unlock(&philosophers->params->mutex);
	}
	return (0);
}
