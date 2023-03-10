/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:54:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/08 16:47:14 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"

extern	SUITE(check_args_suite);
extern	SUITE(init_forks_suite);
extern	SUITE(init_philos_suite);
extern	SUITE(free_forks_suite);
extern	SUITE(free_philos_suite);

GREATEST_MAIN_DEFS();

int	main(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(check_args_suite);
	RUN_SUITE(init_forks_suite);
	RUN_SUITE(init_philos_suite);
	/* RUN_SUITE(free_forks_suite); */
	/* RUN_SUITE(free_philos_suite); */
	GREATEST_MAIN_END();
}
