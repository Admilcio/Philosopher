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

static void	ft_amount_to_eat(t_table *table, unsigned int i, unsigned int *n)
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
			ft_amount_to_eat(table, i, &j);
			if ((table->philo[i].required_meals == -1
					|| table->philo[i].required_meals > 0) && (ft_gettimeofday_ms()
					- table->philo[i].t_last_meal > table->t_to_die))
			{
				ft_death_eaten(table, i);
				return ;
			}
			pthread_mutex_unlock(&table->philo[i].philo_lock);
			i++;
		}
	}
}

static bool	is_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_valid_input(int argc, char **argv)
{
	int		i;
	long	value;

	value = 0;
	i = 1;
	while (i < argc)
	{
		if (is_only_digit(argv[i]) == false)
		{
			printf("Invalid input in [%s]. Only digit accepted.\n", argv[i]);
			return (false);
		}
		value = ft_ato_long(argv[i]);
		if (value < 0 || value > LONG_MAX)
		{
			printf("Invalid input in [%ld]. Negative or so long.\n", value);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	is_valid_args(int ac, char **av, t_table *table)
{
	if (ac < 5 || ac > 6)
		return (false);
	if (table->n_philo > 200)
	{
		printf("Invalid input in [%i].\n", table->n_philo);
		return (false);
	}
	if (is_valid_input(ac, av) == false)
		return(false);
	if (ft_atoi(av[1]) > 200)
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	static t_table	table;

	if (is_valid_args(ac, av, &table) == true)
	{
		ft_init_table(&table, av);
		if (table.fork)
			ft_create_forks(&table);
		if (table.philo && table.fork)
			ft_create_philo(&table);
		if (table.philo)
			ft_has_died(&table);
		if (table.philo)
			ft_wait_threads(&table);
	}
	ft_exit(&table);
	return (0);
}
