/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>  <ada-mata <mar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:03:10 by ada-mata <m       #+#    #+#             */
/*   Updated: 2024/11/16 18:03:10 by ada-mata <m      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_check_stop_habits(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	if (philo->required_meals == 0 || philo->stop == true)
	{
		pthread_mutex_unlock(&philo->philo_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->philo_lock);
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

void	ft_eating(t_philo *philo)
{
	if (philo->left_fork && philo->right_fork)
	{
		pthread_mutex_lock(&philo->philo_lock);
		philo->t_last_meal = ft_gettimeofday_ms();
		ft_print_log(philo, "is eating", philo->t_last_meal);
		if (philo->required_meals > 0)
			philo->required_meals--;
		if (philo->required_meals == 0)
			philo->stop = true;
		pthread_mutex_unlock(&philo->philo_lock);
		ft_wait_until_time(philo->t_to_eat, philo);
	}
}

void	ft_sleeping(t_philo *philo)
{
	ft_print_log(philo, "is sleeping", ft_gettimeofday_ms());
	if (philo->left_fork)
		pthread_mutex_unlock(&philo->left_fork->fork);
	if (philo->right_fork)
		pthread_mutex_unlock(&philo->right_fork->fork);
	ft_wait_until_time(philo->t_to_sleep, philo);
}

void	ft_thinking(t_philo *philo)
{
	ft_print_log(philo, "is thinking", ft_gettimeofday_ms());
	ft_wait_until_time(philo->t_to_think, philo);
}
