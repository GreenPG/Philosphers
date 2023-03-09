/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:38:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/09 15:30:49 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_values(t_philo **philos, char **av, int i,
	pthread_mutex_t time_mut)
{
	philos[i]->id = i + 1;
	philos[i]->t_die = ft_atoi(av[1]);
	philos[i]->t_eat = ft_atoi(av[2]);
	philos[i]->t_sleep = ft_atoi(av[3]);
	philos[i]->state = start;
	philos[i]->time_mut = time_mut;
	if (av[4])
		philos[i]->nb_eat = ft_atoi(av[4]);
}

static void	init_mutexs(t_philo **philos, t_forks *forks, int i)
{
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
}

static void	init_philo_loop(t_philo **philos, t_forks *forks, char **av)
{
	int				i;
	pthread_mutex_t	time_mut;

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
		init_values(philos, av, i, time_mut);
		init_mutexs(philos, forks, i);
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
	if (ac == 4)
		av[4] = NULL;
	init_philo_loop(philos, forks, av);
	return (philos);
}
