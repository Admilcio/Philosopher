/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>  <ada-mata <mar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:04:25 by ada-mata <m       #+#    #+#             */
/*   Updated: 2024/11/16 18:04:25 by ada-mata <m      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	ft_isdigit(int c)
{
	bool	result;

	result = (c >= '0' && c <= '9');
	return (result);
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
			return (false);
		value = ft_ato_long(argv[i]);
		if (value <= 0 || value > LONG_MAX)
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (false);
	if (is_valid_input(ac, av) == false)
		return(false);
	if (ft_atoi(av[1]) > 200)
		return (false);
	return (true);
}
