/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 23:39:18 by djmekki           #+#    #+#             */
/*   Updated: 2022/12/31 21:44:16 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->n % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->fork_r]);
		pthread_mutex_lock(&philo->data->forks[philo->fork_l]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->fork_l]);
		pthread_mutex_lock(&philo->data->forks[philo->fork_r]);
	}
	if (!chck_death(philo))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%-6lu %d has taken a fork\n", current_timestamp() \
			- philo->t_start, philo->n);
		printf("%-6lu %d has taken a fork\n", current_timestamp() \
			- philo->t_start, philo->n);
		pthread_mutex_unlock(&philo->data->print);
	}
}

void	eat(t_philo	*philo)
{
	take_forks(philo);
	if (!chck_death(philo))
	{
		printf("%-6lu %d is eating\n", current_timestamp() - philo->t_start,
			philo->n);
		last_meal(philo);
		meals_nb(philo);
		ms_sleep(philo->data->t_eat);
	}
	pthread_mutex_unlock(&philo->data->forks[philo->fork_l]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_r]);
}

void	ph_sleep(t_philo *philo)
{
	if (!chck_death(philo))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%-6lu %d is sleeping\n", current_timestamp() - philo->t_start,
			philo->n);
		pthread_mutex_unlock(&philo->data->print);
		ms_sleep(philo->data->t_sleep);
	}
}

void	think(t_philo *philo)
{
	if (!chck_death(philo))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%-6lu %d is thinking\n", current_timestamp() - philo->t_start,
			philo->n);
		pthread_mutex_unlock(&philo->data->print);
		usleep(500);
	}
}

void	die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%-6lu %d died\n", current_timestamp() - philo->t_start,
		philo->n);
	pthread_mutex_unlock(&philo->data->print);
	death(philo);
}
