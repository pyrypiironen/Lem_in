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
	lem_data	*flow;

	data = (lem_data *)malloc(sizeof(lem_data));
	flow = (lem_data *)malloc(sizeof(lem_data));
	if (data == NULL || flow == NULL)
		exit(0);
	input(flow);
	copy_input(flow, data);
	solve_paths(data);
	solve_flow(flow);
	if (argc == 2 && ft_strcmp(argv[1], "-t") == 0)
	{

		ft_printf("{green}>>>> flow: %d, rec: %d <<<<\n", flow->best_moves, data->best_moves);
		ft_printf("{yellow}%s\n", flow->optimized);

		ft_printf("{purple}path_index: %d || used routes: %d\n", data->path_index, data->routes_best->route_count);
		return (0);
	}
	if (argc == 2 && ft_strcmp(argv[1], "-m") == 0)
	{
		if (flow->best_moves < data->best_moves)
			ft_printf(">>>> %d <<<<\n", flow->best_moves);
		else
			ft_printf(">>>> %d <<<<\n", data->best_moves);
		return (0);
	}
	print_input(flow);
	if (flow->best_moves < data->best_moves)
		send_ants(flow);
	else
		send_ants(data);
	return (0);
}

void	copy_input(lem_data *d, lem_data *f)
{
	f->head = d->head;
	f->current = d->current;
	f->start = d->start;
	f->end = d->end;
	f->ants = d->ants;
	f->path_limit = d->path_limit;
	f->route = d->route;
	f->room_count = d->room_count;
}
