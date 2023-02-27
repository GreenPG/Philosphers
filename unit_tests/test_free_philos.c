/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free_philos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:29:26 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/25 15:57:04 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include <philo.h>

///////////////////////////////////////////////////////////////////////////////
/// ASSERTIONS

///////////////////////////////////////////////////////////////////////////////
///	TESTS

TEST	full_tab(void)	{
	char	**ipt1 = malloc(sizeof(char *) * 5);
	ipt1[0] = "4";
	ipt1[1] = "300";
	ipt1[2] = "300";
	ipt1[3] = "300";
	t_philo **p1 = init_philos(ipt1, 4); 
	char	**ipt2 = malloc(sizeof(char *) * 6);
	ipt2[0] = "4";
	ipt2[1] = "300";
	ipt2[2] = "300";
	ipt2[3] = "300";
	ipt2[4] = "300";
	t_philo **p2 = init_philos(ipt2, 5); 

	free_philos(&p1);
	ASSERT_EQ_FMT(NULL, p1, "%p");
	free_philos(&p2);
	ASSERT_EQ_FMT(NULL, p2, "%p");
	free(ipt1);
	free(ipt2);
	PASS();
}

TEST	empty_pointer(void) {
	t_philo **p1 = NULL;

	free_philos(&p1);
	ASSERT_EQ_FMT(NULL, p1, "%p");
	PASS();
}
///////////////////////////////////////////////////////////////////////////////
///	SUITE

SUITE(free_philos_suite)	{
	RUN_TEST(full_tab);
	RUN_TEST(empty_pointer);
}
