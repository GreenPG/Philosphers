/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:53:50 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/25 11:25:51 by gpasquet         ###   ########.fr       */
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
	s_free(tmp->tab);
	free(*forks);
	*forks = NULL;
}

void	free_philos()
{

}
