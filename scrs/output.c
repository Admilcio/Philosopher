/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>  <ada-mata <mar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:03:24 by ada-mata <m       #+#    #+#             */
/*   Updated: 2024/11/16 18:03:24 by ada-mata <m      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_log_status(t_philo *philo, char *message, unsigned long time)
{
	pthread_mutex_lock(&philo->table->log_mutex);
	if (philo->table->is_dead == false)
	{
		printf("%lu %d %s\n", time - philo->t_start, philo->id, message);
	}
	pthread_mutex_unlock(&philo->table->log_mutex);
}

void	ft_synch_all_philo(t_philo *philo)
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
