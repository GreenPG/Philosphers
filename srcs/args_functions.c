/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:38:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/08 17:30:35 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <string.h>

static pthread_mutex_t	*init_forks_tab(int philo_nb )
{
	pthread_mutex_t	*tab;
	int				i;

	tab = malloc(sizeof(pthread_mutex_t) * philo_nb);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < philo_nb)
	{
		pthread_mutex_init(&tab[i], NULL);
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
	int				i;
	pthread_mutex_t time_mut;

	pthread_mutex_init(&time_mut, NULL);
	i = 0;
	while (i < forks->philo_nb)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			free_philos(&philos, forks->philo_nb);
			return ;
		}
		philos[i]->id = i + 1;
		philos[i]->t_die = ft_atoi(av[1]);
		philos[i]->t_eat = ft_atoi(av[2]);
		philos[i]->t_sleep = ft_atoi(av[3]);
		philos[i]->state = start;
		philos[i]->time_mut = time_mut;
		if (ac == 5)
			philos[i]->nb_eat = ft_atoi(av[4]);
		if (i == forks->philo_nb - 1)
		{
			philos[i]->forks[0] = &forks->tab[i];
			philos[i]->forks[1] = &forks->tab[0];
		}
		else
		{
			philos[i]->forks[0] = &forks->tab[i];
			philos[i]->forks[1] = &forks->tab[i + 1];
		}
		i++;
	}
}

t_philo	**init_philos(char **av, int ac, t_forks *forks)
{
	t_philo	**philos;

	if (!av || ac < 4 || ac > 5)
		return (NULL);
	philos = malloc(sizeof(t_philo *) * forks->philo_nb);
	if (!philos)
		return (NULL);
	init_philo_loop(philos, forks, av, ac);
	return (philos);
}
