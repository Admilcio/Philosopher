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

void	ft_create_philo(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (ft_init_philo(&table->philo[i], table, i) == false)
		{
			ft_clear_all(table);
			return ;
		}
		i++;
	}
	pthread_mutex_lock(&table->access_mutex);
	table->dinner_started = true;
	pthread_mutex_unlock(&table->access_mutex);
}

void	ft_create_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (!ft_init_forks(&table->fork[i], i))
		{
			ft_clear_all(table);
			return ;
		}
		i++;
	}
}
