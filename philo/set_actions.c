/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 07:45:33 by djmekki           #+#    #+#             */
/*   Updated: 2022/12/31 20:09:57 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->last);
	philo->last_eat = current_timestamp();
	pthread_mutex_unlock(&philo->data->last);
}

void	meals_nb(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meals);
	++philo->meals;
	pthread_mutex_unlock(&philo->data->meals);
}

void	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	philo->data->stop_s = 1;
	pthread_mutex_unlock(&philo->data->death);
}
