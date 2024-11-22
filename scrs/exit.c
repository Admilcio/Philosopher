/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>  <ada-mata <mar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:04:04 by ada-mata <m       #+#    #+#             */
/*   Updated: 2024/11/16 18:04:04 by ada-mata <m      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	return (1);
}

static void	ft_clear_philos(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->n_philo && &table->philo[i])
	{
		pthread_mutex_destroy(&table->philo[i].philo_lock);
		i++;
	}
}

static void	ft_clear_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->n_philo && table->fork[i].found)
	{
		pthread_mutex_destroy(&table->fork[i].fork);
		i++;
	}
}

static void	ft_clear_table(t_table *table)
{
	if (table)
	{
		if (!table->philo)
			return ;
		if (table->philo)
			free(table->philo);
		if (!table->fork)
			return ;
		if (table->fork)
			free(table->fork);
		pthread_mutex_destroy(&table->access_mutex);
		pthread_mutex_destroy(&table->log_mutex);
	}
}

void	ft_clear_all(t_table *table)
{
	ft_clear_philos(table);
	ft_clear_forks(table);
	ft_clear_table(table);
}