/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>  <ada-mata <mar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:49:41 by ada-mata <m       #+#    #+#             */
/*   Updated: 2024/11/22 21:49:41 by ada-mata <m      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_get_started(t_table *table)
{
	while (1)
	{
		usleep(200);
		pthread_mutex_lock(&table->access_mutex);
		if (table->dinner_started == true)
		{
			pthread_mutex_unlock(&table->access_mutex);
			return ;
		}
		pthread_mutex_unlock(&table->access_mutex);
	}
}

static void	ft_routine(t_philo *philo)
{
	while (1)
	{
		ft_take_forks(philo);
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
		if (ft_stop_routine_check(philo) == true)
			return ;
	}
}

void	*ft_run_routine(void *philosopher)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)philosopher;
	table = philo->table;
	ft_get_started(table);
	ft_synch_all_philo(philo);
	ft_routine(philo);
	return (NULL);
}
