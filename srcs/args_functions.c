/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:38:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/27 14:29:32 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <string.h>

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
	forks = malloc(sizeof(t_forks));
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
		free_forks(&forks);
		return (NULL);
	}
	return (forks);
}

static void	init_philo_loop(t_philo **philos, t_forks *forks, char **av, int ac)
{
	int		i;

	i = 0;
	while (i < forks->philo_nb)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			free_philos(&philos);
			return ;
		}
		philos[i]->forks = forks;
		philos[i]->id = i + 1;
		philos[i]->t_die = ft_atoi(av[1]);
		philos[i]->t_eat = ft_atoi(av[2]);
		philos[i]->t_sleep = ft_atoi(av[3]);
		philos[i]->state = start;
		if (ac == 5)
			philos[i]->nb_eat = ft_atoi(av[4]);
		i++;
	}
}

t_philo	**init_philos(char **av, int ac)
{
	t_philo	**philos;
	t_forks	*forks;

	if (!av || ac < 4 || ac > 5)
		return (NULL);
	forks = init_forks(av[0]);
	if (!forks)
		return (NULL);
	philos = malloc(sizeof(t_philo *) * forks->philo_nb);
	if (!philos)
		return (NULL);
	init_philo_loop(philos, forks, av, ac);
	return (philos);
}
