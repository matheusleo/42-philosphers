/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:12:52 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/28 13:41:02 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	init_sim(t_sim *simulation)
{
	size_t	i;

	i = 0;
	create_forks(simulation);
	create_philos(simulation);
	init_monitor(simulation);
	init_philos(simulation);
	simulation->start_time = get_current_time();
	pthread_join(simulation->monitor, NULL);
	while (i < simulation->nb_philo)
	{
		pthread_join(simulation->philos[i]->thread, NULL);
		i++;
	}
	return (NO_ERR);
}

static int	end_sim(t_sim *simulation)
{
	destroy_forks(simulation);
	destroy_philos(simulation);
	free(simulation);
	return (NO_ERR);
}

int	main(int argc, char *argv[])
{
	t_sim	*simulation;
	int		err;

	simulation = NULL;
	err = validate_args(argc, argv);
	if (err)
		return (err);
	simulation = parse_args(argc, argv);
	init_sim(simulation);
	end_sim(simulation);
}
