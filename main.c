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
		return (ft_error(INV_ARGS));
	if (!ft_initialize_simulation(&table, av))
		return (ft_error(FAIL));
	ft_check_simulation(&table);
	ft_clear_all(&table);
	return (0);
}
