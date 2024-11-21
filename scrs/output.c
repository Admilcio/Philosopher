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

void	ft_create_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (!ft_init_forks(&table->fork[i], i))
		{
			ft_exit(table);
			return ;
		}
		i++;
	}
}

void	ft_check_forks(t_philo *philo)
{
	if (philo->id % 2 == 1 && philo->left_fork != NULL)
		pthread_mutex_lock(&philo->left_fork->fork);
	else if (philo->right_fork != NULL)
		pthread_mutex_lock(&philo->right_fork->fork);
	ft_print_log(philo, "has taken a fork", ft_gettimeofday_ms());
	if (philo->table->n_philo != 1)
	{
		if (philo->id % 2 == 1 && philo->right_fork != NULL)
			pthread_mutex_lock(&philo->right_fork->fork);
		else if (philo->left_fork != NULL)
			pthread_mutex_lock(&philo->left_fork->fork);
		ft_print_log(philo, "has taken a fork", ft_gettimeofday_ms());
	}
}

void	ft_print_log(t_philo *philo, char *message, unsigned long time)
{
	pthread_mutex_lock(&philo->table->log_mutex);
	if (philo->table->is_dead == false)
	{
		printf("%lu %d %s\n", time - philo->t_start, philo->id, message);
	}
	pthread_mutex_unlock(&philo->table->log_mutex);
}

void	ft_death_eaten(t_table *table, int id)
{
	pthread_mutex_lock(&table->log_mutex);
	printf("%ld %d died\n", ft_gettimeofday_ms() - table->t_start,
		table->philo[id].id);
	table->is_dead = true;
	pthread_mutex_unlock(&table->log_mutex);
	pthread_mutex_unlock(&table->philo[id].philo_lock);
	ft_stop_dinner(table);
}
