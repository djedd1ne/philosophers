/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 02:45:34 by djmekki           #+#    #+#             */
/*   Updated: 2022/12/31 22:53:40 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct timeval	t_time;

typedef struct s_data{
	int				n_of_philo;
	unsigned long	t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	int				philo_ate;
	int				stop_s;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	last;
	pthread_mutex_t	meals;
}			t_data;

typedef struct s_philo{
	int				n;
	t_data			*data;
	pthread_t		thread;
	int				fork_l;
	int				fork_r;
	unsigned long	t_start;
	unsigned long	last_eat;
	int				meals;
	int				finished;
}			t_philo;

// libft_utils
int				ft_isdigit(int c);
long			ft_atoi(const char *str);

// philo_utils.c
unsigned long	current_timestamp(void);
void			ms_sleep(unsigned long time);
void			free_philos(t_philo **philos);
void			free_data(t_data *data);

// set_actions.c
void			last_meal(t_philo *philo);
void			meals_nb(t_philo *philo);
void			death(t_philo *philo);

// chck_actions
int				chck_death(t_philo *philo);
int				chck_meals(t_philo *philo);
unsigned long	chck_last_meal(t_philo *philo);
int				chck_philo(t_philo **philo, t_data *data);

// init.c
t_data			*parse_data(char **argv);
t_philo			**init_philo(t_data *data);
void			init_mutex(t_data *data);

// philo_life.c
void			take_forks(t_philo *philo);
void			eat(t_philo	*philo);
void			ph_sleep(t_philo *philo);
void			think(t_philo *philo);
void			die(t_philo *philo);

// philo.c
void			one_philo(t_philo *philo);
void			routine(t_philo *philo);
void			chck_arg(int ac, char **av);
#endif
