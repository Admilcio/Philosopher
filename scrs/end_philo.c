/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>  <ada-mata <mar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:50:12 by ada-mata <m       #+#    #+#             */
/*   Updated: 2024/11/22 19:50:12 by ada-mata <m      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_check_required_meal(t_table *table, unsigned int i,
		unsigned int *n)
{
	if (table->philo[i].required_meals == 0)
		*n += 1;
	if (*n == table->n_philo)
		table->is_fed = true;
}

void	ft_philo_died(t_table *table, int id)
{
	pthread_mutex_lock(&table->log_mutex);
	printf("%ld %d died\n", ft_get_time_ms() - table->t_start,
		table->philo[id].id);
	table->is_dead = true;
	pthread_mutex_unlock(&table->log_mutex);
	pthread_mutex_unlock(&table->philo[id].philo_lock);
	ft_stop_dinner(table);
}

static bool	ft_check_philo(t_table *table, unsigned int i, unsigned int *j)
{
	pthread_mutex_lock(&table->philo[i].philo_lock);
	ft_check_required_meal(table, i, j);
	if ((table->philo[i].required_meals == -1
			|| table->philo[i].required_meals > 0)
		&& (ft_get_time_ms() - table->philo[i].t_last_meal > table->t_to_die))
	{
		ft_philo_died(table, i);
		return (true);
	}
	pthread_mutex_unlock(&table->philo[i].philo_lock);
	return (false);
}

void	ft_stop_dinner(t_table *table)
{
	unsigned int	i;

	i = -1;
	while (++i < table->n_philo)
	{
		pthread_mutex_lock(&table->philo[i].philo_lock);
		table->philo[i].stop = true;
		pthread_mutex_unlock(&table->philo[i].philo_lock);
	}
}

void	ft_has_died(t_table *table)
{
	unsigned int	i;
	unsigned int	j;

	usleep(6000);
	while (table->is_dead == false && table->is_fed == false)
	{
		i = 0;
		j = 0;
		usleep(1000);
		while (i < table->n_philo)
		{
			if (ft_check_philo(table, i, &j))
				return ;
			i++;
		}
	}
}
