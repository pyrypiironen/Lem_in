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

#include "../../includes/lem_in.h"

int	main(int argc, char **argv)
{
	lem_data	*data;

	data = (lem_data *)malloc(sizeof(lem_data));
	if (data == NULL)
		exit(0);
	input(data);
	solve_paths(data);
	// 	for (int i = 0; i < data->path_index; i++)
	// {
	// 	for (int j = 0; data->paths[i][j] != data->end; j++)
	// 		ft_printf("{red}%s -> ", data->paths[i][j]->name);
	// 	ft_printf("{red}%s -> ", data->end->name);
	// 	ft_printf("\n");
	// }
	if (argc == 2 && ft_strcmp(argv[1], "-m") == 0)
	{
		ft_printf(">>>> %d <<<<\n", data->best_moves);
		return (0);
	}
	print_input(data);
	send_ants(data);
	return (0);
}
