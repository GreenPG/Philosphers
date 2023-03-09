/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:26:05 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/09 15:28:05 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
