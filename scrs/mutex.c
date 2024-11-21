/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>  <ada-mata <mar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:03:33 by ada-mata <m       #+#    #+#             */
/*   Updated: 2024/11/16 18:03:33 by ada-mata <m      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_get_started(t_table *table)
{
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&table->access_mutex);
		if (table->dinner_started == true)
		{
			pthread_mutex_unlock(&table->access_mutex);
			return ;
		}
		pthread_mutex_unlock(&table->access_mutex);
	}
}

static void	ft_synchornize(t_philo *philo)
{
	if (philo->table->n_philo % 2 == 1)
	{
		if ((unsigned int)philo->id == philo->table->n_philo)
			ft_wait_until_time(philo->t_to_eat * 2, philo);
		else if (philo->id % 2 == 1)
			ft_wait_until_time(philo->t_to_eat, philo);
	}
	else if (philo->id % 2 == 0)
		ft_wait_until_time(philo->t_to_eat, philo);
}

static void	ft_habits(t_philo *philo)
{
	while (1)
	{
		ft_check_forks(philo);
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
		if (ft_check_stop_habits(philo) == true)
			return ;
	}
}

void	*ft_routine(void *philosopher)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)philosopher;
	table = philo->table;
	ft_get_started(table);
	ft_synchornize(philo);
	ft_habits(philo);
	return (NULL);
}

void	ft_create_philo(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (ft_init_philo(&table->philo[i], table, i) == false)
		{
			ft_exit(table);
			return ;
		}
		i++;
	}
	pthread_mutex_lock(&table->access_mutex);
	table->dinner_started = true;
	pthread_mutex_unlock(&table->access_mutex);
}
