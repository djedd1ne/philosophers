/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 02:45:11 by djmekki           #+#    #+#             */
/*   Updated: 2023/01/01 00:17:10 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork_r]);
	printf("%-6lu %d has taken a fork\n", current_timestamp() - philo->t_start,
		philo->n);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_r]);
}

void	routine(t_philo *philo)
{
	philo->t_start = current_timestamp();
	last_meal(philo);
	if (philo->data->n_of_philo == 1)
		return (one_philo(philo));
	if (philo->n % 2 == 0)
		ms_sleep(1);
	while (!chck_death(philo))
	{
		eat(philo);
		ph_sleep(philo);
		think(philo);
	}
}

int	str_isdigit(char *str)
{
	while (*str)
	{
		if (!((*str >= '0' && *str <= '9') || \
			(*str == '+' && *(str + 1) != '+')))
			return (0);
		++str;
	}
	return (1);
}

int	chck_av(char **av)
{
	char	**p_str;

	p_str = av;
	while (*p_str)
	{
		if (!str_isdigit(*p_str) || ft_atoi(*p_str) < 1
			|| ft_atoi(*p_str) > 2147483647)
			return (1);
		++p_str;
	}
	return (0);
}

void	chck_arg(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Usage : ./philo n_of_philo t_die t_eat t_sleep | n_must_eat\n");
		exit(1);
	}
	else if (chck_av(av))
	{
		printf("Invalid numbers usage\n");
		exit(1);
	}
	return ;
}
