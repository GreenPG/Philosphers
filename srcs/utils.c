/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:25:36 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/14 16:58:44 by gpasquet         ###   ########.fr       */
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
	static struct timeval	start_time;
	long long				time;

	if (par <= 1)
	{
		if (par == 0)
			gettimeofday(&start_time, NULL);
		return (0);
	}
	gettimeofday(&tmval, NULL);
	time = (tmval.tv_sec - start_time.tv_sec) * 1000
		+ (tmval.tv_usec - start_time.tv_usec) / 1000;
	return (time);
}

void	change_status(enum e_state status, t_philo *data, long int time)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	if (status != take)
		data->state = status;
	if (status == take)
		printf("\033[1;33m%li Philo %i has taken a fork\n\033[0m", time, data->id);
	else if (status == sleeping)
		printf("\033[1;36m%li Philo %i start to sleep\n\033[0m", time, data->id);
	else if (status == eating)
		printf("\033[1;32m%li Philo %i start to eat\n\033[0m", time, data->id);
	else if (status == thinking)
		printf("\033[1;35m%li Philo %i start to think\n\033[0m", time, data->id);
	else
		printf("\033[1;31m%li Philo %i died\n\033[0m", time, data->id);
	pthread_mutex_unlock(&mutex);
}
