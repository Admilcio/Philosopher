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

bool	ft_stop_routine_check(t_philo *philo)
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

void	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1 && philo->left_fork != NULL) // Philo = 1 checked 
		pthread_mutex_lock(&philo->left_fork->fork);
	else if (philo->right_fork != NULL)
		pthread_mutex_lock(&philo->right_fork->fork);
	ft_log_status(philo, "has taken a fork", ft_get_time_ms());
	if (philo->table->n_philo != 1)
	{
		if (philo->id % 2 == 1 && philo->right_fork != NULL)
			pthread_mutex_lock(&philo->right_fork->fork);
		else if (philo->left_fork != NULL)
			pthread_mutex_lock(&philo->left_fork->fork);
		ft_log_status(philo, "has taken a fork", ft_get_time_ms());
	}
}

void	ft_eating(t_philo *philo)
{
	if (philo->left_fork && philo->right_fork)
	{
		pthread_mutex_lock(&philo->philo_lock);
		philo->t_last_meal = ft_get_time_ms();
		ft_log_status(philo, "is eating", philo->t_last_meal);
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
	ft_log_status(philo, "is sleeping", ft_get_time_ms());
	if (philo->left_fork)
		pthread_mutex_unlock(&philo->left_fork->fork);
	if (philo->right_fork)
		pthread_mutex_unlock(&philo->right_fork->fork);
	ft_wait_until_time(philo->t_to_sleep, philo);
}

void	ft_thinking(t_philo *philo)
{
	ft_log_status(philo, "is thinking", ft_get_time_ms());
	ft_wait_until_time(philo->t_to_think, philo);
}
