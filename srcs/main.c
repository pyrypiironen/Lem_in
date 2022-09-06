/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:27:58 by ppiirone          #+#    #+#             */
/*   Updated: 2022/08/21 15:28:01 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	main(void)
{




	lem_data	*data;

	data = (lem_data *)malloc(sizeof(lem_data));
		if (data == NULL)
			exit(0);
	input(data);
	solve_paths(data);
	


	// while (data->head)
	// {
	// 	int i = 0;
	// 	ft_printf("{green}room %s floor: %d:\n", data->head->name, data->head->floor);
	// 	while (i < data->head->pipe_count)
	// 	{
	// 		ft_printf("link: %s\n", data->head->pipes[i]->name);
	// 		//data->head = data->head->next;
	// 		i++;
	// 	}
	// 	data->head = data->head->next;
	// }
	for (int i = 0; i < 5; i++)
	{
		ft_printf("{red}route %d\n", i);
		for (int j = 0; j < 5; j++)
		{
			ft_printf("%s\n", data->paths[i][j]->name);
		}
	}
	exit(0);




	return (0);
}
