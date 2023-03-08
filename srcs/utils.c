/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:25:36 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/07 16:53:38 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			ret;
	int			sign;

	i = 0;
	ret = 0;
	sign = 1;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		ret = (ret * 10) + (nptr[i] - 48);
		i++;
	}
	ret *= sign;
	return (ret);
}

long long	get_set_time(int par)
{
	struct timeval			tmval;
	static struct timeval	*start_time;
	static pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	if (par == 0)
	{
		pthread_mutex_lock(&mutex);
		if (!start_time)
		{
			start_time = malloc(sizeof(struct timeval));
			gettimeofday(start_time, NULL);
		}
		pthread_mutex_unlock(&mutex);
		return (start_time->tv_sec * 1000 + start_time->tv_usec / 1000);
	}
	pthread_mutex_lock(&mutex);
	gettimeofday(&tmval, NULL);
	pthread_mutex_unlock(&mutex);
	return (tmval.tv_sec * 1000 + tmval.tv_usec / 1000);
}
