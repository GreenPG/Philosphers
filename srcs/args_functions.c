/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:38:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/25 09:37:09 by gpasquet         ###   ########.fr       */
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
		if (ft_strlen(av[i]) > 10)
			return (-1);
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

static int	*init_forks_tab(int philo_nb )
{
	int	*tab;
	int	i;

	tab = malloc(sizeof(int) * philo_nb);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < philo_nb)
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}

t_forks	*init_forks(char *input)
{
	t_forks	*forks;

	if (!input)
		return (NULL);
	forks = malloc(sizeof(forks));
	if (!forks)
		return (NULL);
	forks->philo_nb = ft_atoi(input);
	if (forks->philo_nb <= 0)
	{
		free(forks);
		return (NULL);
	}
	forks->tab = init_forks_tab(forks->philo_nb);
	if (!forks->tab)
	{
	//	free_forks(forks);
		return (NULL);
	}
	return (forks);
}

t_philo	**init_philos(char **av, int ac)
{
	t_philo	**philos;
	t_forks	*forks;
	int		i;

	if (!av || ac < 4 || ac > 5)
		return (NULL);
	forks = init_forks(av[0]);
	if (!forks)
		return (NULL);
	philos = malloc(sizeof(*philos) * ac + 1);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < ac)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			//free_philos(philos);
			return (NULL);
		}
		philos[i]->forks = forks;
		philos[i]->id = i + 1;
		philos[i]->t_die = ft_atoi(av[1]);
		philos[i]->t_eat = ft_atoi(av[2]);
		philos[i]->t_sleep = ft_atoi(av[3]);
		if (ac == 5)
			philos[i]->nb_eat = ft_atoi(av[4]);
		i++;
	}
	philos[ac] = NULL;
	return (philos);
}
