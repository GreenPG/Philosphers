/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_death.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:01:11 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/13 16:34:45 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>
#include "../greatest/greatest.h"

///////////////////////////////////////////////////////////////////////////////
/// ASSERTIONS

TEST	ASSERT_DEATH_EQ(t_death *actual, t_philo **ph) {
	int	i = 0;

	ASSERT_EQ_FMT(4, actual->nb_philo, "%i");
	ASSERT_EQ_FMT(0, (int)actual->t_die, "%i");
	ASSERT_EQ_FMT(0, actual->finished_ph, "%i");
	while (i < actual->nb_philo)
	{
		ASSERT_MEM_EQ((void *)ph[i], (void *)actual->philos[i], sizeof(t_philo *));
		i++;
	}
	PASS();
}
///////////////////////////////////////////////////////////////////////////////
///	TESTS

TEST	simple_input(void) {
	t_forks	*forks = init_forks("4");
	char	*args1[4] = {"4", "300", "100", "100"};
	char	*args2[5] = {"4", "300", "100", "100", "4"};
	t_philo	**phs1 = init_philos(args1, 4, forks);
	if (!forks)
		forks = init_forks("4");
	t_philo	**phs2 = init_philos(args2, 5, forks);

	CHECK_CALL(ASSERT_DEATH_EQ(init_death(phs1, 4), phs1));
	CHECK_CALL(ASSERT_DEATH_EQ(init_death(phs2, 4), phs2));
	PASS();
}

///////////////////////////////////////////////////////////////////////////////
///	SUITE

SUITE(init_death_suite) {
	RUN_TEST(simple_input);
}
