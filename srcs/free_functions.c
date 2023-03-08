/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:53:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/08 16:46:33 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	s_free(void *elem)
{
	if (elem != NULL)
	{
		free(elem);
		elem = NULL;
	}
}

void	free_forks(t_forks **forks)
{
	t_forks	*tmp;

	if (!forks || !*forks)
		return ;
	tmp = *forks;
	if (tmp->tab)
	{
		pthread_mutex_destroy(tmp->tab);
		free(tmp->tab);
	}
	free(*forks);
	*forks = NULL;
	tmp = NULL;
}

void	free_philos(t_philo ***philos, int nb_philo)
{
	t_philo	**tmp;
	int		i;

	if (!philos | !*philos)
		return ;
	tmp = *philos;
	i = 0;
	while (i < nb_philo)
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(*philos);
	*philos = NULL;
}
