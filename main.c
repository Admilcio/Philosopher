/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>  <ada-mata <mar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:03:19 by ada-mata <m       #+#    #+#             */
/*   Updated: 2024/11/16 18:03:19 by ada-mata <m      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static void	ft_wait_threads(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->n_philo)
		pthread_join(table->philo[i++].philo_thread, NULL);
}

static void	ft_required_meal(t_table *table, unsigned int i, unsigned int *n)
{
	if (table->philo[i].required_meals == 0)
		*n += 1;
	if (*n == table->n_philo)
		table->is_fed = true;
}

static void	ft_has_died(t_table *table)
{
	unsigned int	i;
	unsigned int	j;

	usleep(6000);
	while (table->is_dead == false && table->is_fed == false)
	{
		i = 0;
		j = 0;
		while (i < table->n_philo)
		{
			usleep(1000);
			pthread_mutex_lock(&table->philo[i].philo_lock);
			ft_required_meal(table, i, &j);
			if ((table->philo[i].required_meals == -1
					|| table->philo[i].required_meals > 0) && (ft_get_time_ms()
					- table->philo[i].t_last_meal > table->t_to_die))
			{
				ft_philo_died(table, i);
				return ;
			}
			pthread_mutex_unlock(&table->philo[i].philo_lock);
			i++;
		}
	}
}

bool	ft_initialize_simulation(t_table *table, char **av)
{
	ft_init_table(table, av);
	if (table->fork)
		ft_create_forks(table);
	if (table->philo && table->fork)
		ft_create_philo(table);
	return (table->philo != NULL && table->fork != NULL);
}

void	ft_check_simulation(t_table *table)
{
	if (table->philo)
		ft_has_died(table);
	if (table->philo)
		ft_wait_threads(table);
}


int	main(int ac, char **av)
{
	static t_table	table;

	if (!is_valid_args(ac, av))
		return (ft_error("Invalid arguments"));
	if (!ft_initialize_simulation(&table, av))
		return (ft_error("Failed to initialize simulation"));
	ft_check_simulation(&table);
	ft_exit(&table);
	return (0);
}
