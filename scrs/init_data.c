/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>  <ada-mata <mar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:03:41 by ada-mata <m       #+#    #+#             */
/*   Updated: 2024/11/16 18:03:41 by ada-mata <m      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_init_philo(t_philo *philo, t_table *table, int id)
{
	philo->t_to_die = table->t_to_die;
	philo->t_to_sleep = table->t_to_sleep;
	philo->t_to_eat = table->t_to_eat;
	philo->t_to_think = table->t_to_think;
	philo->t_start = table->t_start;
	philo->t_last_meal = table->t_start;
	philo->required_meals = table->required_meals;
	philo->id = id + 1;
	philo->stop = false;
	philo->left_fork = &table->fork[id];
	if ((unsigned int)philo->id == table->n_philo && table->n_philo != 1)
		philo->right_fork = &table->fork[0];
	else if (table->n_philo != 1)
		philo->right_fork = &table->fork[id + 1];
	else
		philo->right_fork = NULL;
	philo->table = table;
	if (pthread_mutex_init(&philo->philo_lock, NULL) != 0)
		return (false);
	if (pthread_create(&philo->philo_thread, NULL, ft_run_routine,
			philo) != 0)
		return (false);
	return (true);
}

void	ft_init_table(t_table *table, char **av)
{
	table->n_philo = ft_atoi(av[1]);
	table->t_to_die = ft_atoi(av[2]);
	table->t_to_eat = ft_atoi(av[3]);
	table->t_to_sleep = ft_atoi(av[4]);
	table->t_to_think = ft_get_think_time(table);
	table->required_meals = -1;
	table->is_dead = false;
	table->is_fed = false;
	table->dinner_started = false;
	if (av[5])
		table->required_meals = ft_atoi(av[5]);
	if (pthread_mutex_init(&table->access_mutex, NULL) != 0
		|| pthread_mutex_init(&table->log_mutex, NULL) != 0)
	{
		ft_clear_all(table);
		return ;
	}
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philo)
		ft_clear_all(table);
	table->fork = (t_fork *)malloc(sizeof(t_fork) * table->n_philo);
	if (!table->fork)
		ft_clear_all(table);
	table->t_start = ft_get_time_ms();
}

bool	ft_init_forks(t_fork *fork, int id)
{
	fork->id = id;
	fork->found = false;
	if (pthread_mutex_init(&fork->fork, NULL) != 0)
		return (false);
	fork->found = true;
	return (true);
}