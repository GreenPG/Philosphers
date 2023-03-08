/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:24:17 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/08 16:13:51 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <string.h>

static int	check_args_size(int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (ft_strlen(av[i]) > 10 || ft_atoi(av[i]) < 0)
		{
			printf("Parameters %i is superior to int max\n", i);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	check_if_digits(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (i < ac)
	{
		if (!av[i])
			return (-1);
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				write(2, "Arguments must only be digits\n", 30);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	if (ac < 4 || ac > 5)
	{
		write(2, "Invalid numbers of arguments\n", 29);
		return (-1);
	}
	if (check_if_digits(ac, av) == -1)
		return (-1);
	if (check_args_size(ac, av) == -1)
		return (-1);
	return (0);
}
