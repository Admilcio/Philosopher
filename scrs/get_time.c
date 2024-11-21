/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>  <ada-mata <mar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:11:58 by ada-mata <m       #+#    #+#             */
/*   Updated: 2024/11/16 18:11:58 by ada-mata <m      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	ft_get_time_think(t_table *table)
{
	unsigned long	t_to_think;

	if (table->n_philo % 2 == 1)
		t_to_think = table->t_to_eat * 2 - table->t_to_sleep;
	else if (table->t_to_eat > table->t_to_sleep)
		t_to_think = table->t_to_eat - table->t_to_sleep;
	else
		t_to_think = 0;
	return (t_to_think);
}

unsigned long	ft_gettimeofday_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec) * 1000 + (time.tv_usec) / 1000);
}

void	ft_wait_until_time(unsigned long delay_ms, t_philo *philo)
{
	unsigned long	deadline;

	deadline = ft_gettimeofday_ms() + delay_ms;
	while (ft_gettimeofday_ms() <= deadline)
	{
		pthread_mutex_lock(&philo->philo_lock);
		if (philo->stop == true)
		{
			pthread_mutex_unlock(&philo->philo_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->philo_lock);
		usleep(500);
	}
}