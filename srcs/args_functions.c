/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:38:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/16 12:55:20 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	check_args_size(int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (ft_strlen(av[i]) > 10)
			return (-1);
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 4 || ac > 5)
	{
		write(2, "Invalid numbers of arguments\n", 29);
		return (-1);
	}
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
	if (check_args_size(ac, av) == -1)
		return (-1);
	return (0);
}

t_args	*get_args(int ac, char **av)
{
	t_args	*args;

	if (! av || (ac < 4 || ac > 5))
		return (NULL);
	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->args_nb = ac;
	args->tab = malloc(sizeof(int) * ac);
	if (!args->tab)
	{
		free_args(args);
		return (NULL);
	}
	args->tab[0] = ft_atoi(av[0]);
	args->tab[1] = ft_atoi(av[1]);
	args->tab[2] = ft_atoi(av[2]);
	args->tab[3] = ft_atoi(av[3]);
	if (args->tab[0] < 1 || args->tab[1] < 1 || args->tab[2] < 1 || args->tab[3] < 1)
	{
		free_args(args);
		args = NULL;
	}
	if (ac == 5)
	{
		args->tab[4] = ft_atoi(av[4]);
		if (args->tab[4] < 1)
		{
			free_args(args);
			args = NULL;
		}
	}
	return (args);
}
