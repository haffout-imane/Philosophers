/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecircle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihaffout <ihaffout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:23:26 by ihaffout          #+#    #+#             */
/*   Updated: 2024/06/26 16:16:12 by ihaffout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->right_fork);
	pthread_mutex_lock(&philosopher->params->write);
	printf("%lld %d has taken a fork\n", (current_time()
			- philosopher->params->start_simulation), philosopher->id);
	pthread_mutex_unlock(&philosopher->params->write);
	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(&philosopher->params->write);
	printf("%lld %d has taken a fork\n", (current_time()
			- philosopher->params->start_simulation), philosopher->id);
	pthread_mutex_unlock(&philosopher->params->write);
	pthread_mutex_lock(&philosopher->params->write);
	printf("%lld %d is eating\n", (current_time()
			- philosopher->params->start_simulation), philosopher->id);
	pthread_mutex_unlock(&philosopher->params->write);
	pthread_mutex_lock(&philosopher->params->mutex);
	philosopher->last_meal_time = current_time();
	pthread_mutex_unlock(&philosopher->params->mutex);
	usleep(philosopher->params->time_eat);
	pthread_mutex_lock(&philosopher->params->mutex);
	philosopher->meals_eaten++;
	pthread_mutex_unlock(&philosopher->params->mutex);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}

void	thinking(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->params->write);
	printf("%lld %d is thinking\n", (current_time()
			- philosopher->params->start_simulation), philosopher->id);
	pthread_mutex_unlock(&philosopher->params->write);
}

void	sleeping(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->params->write);
	printf("%lld %d is sleeping\n", (current_time()
			- philosopher->params->start_simulation), philosopher->id);
	pthread_mutex_unlock(&philosopher->params->write);
	usleep(philosopher->params->time_sleep);
}

void	*lifecircle(void *philo)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)philo;
	if (!(philosopher->id % 2) 
		|| (philosopher->id == philosopher->params->num_philo))
	{
		thinking(philosopher);
		usleep(philosopher->params->time_eat);
	}
	while (1)
	{
		eating(philosopher);
		sleeping(philosopher);
		thinking(philosopher);
	}
	return (NULL);
}
