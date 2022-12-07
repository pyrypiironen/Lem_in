/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:33:09 by ppiirone          #+#    #+#             */
/*   Updated: 2022/09/22 11:33:11 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	get_unique(lem_data *d)
{
	int		ret;
	int		path_stop;

	init_unique(d);
	flow_routes(d);
	path_stop = d->path_index;
	d->path_index = 0;
	while (1)
	{	
		ret = solution_found(d);
		// ft_printf("route_count: %d, path_limit: %d\n", d->routes_cur->route_count, d->path_limit);
		// ft_printf("{red}ret: %d", ret);

		if (ret == 1)
		{
			get_move_counts(d);
			if (d->routes_cur->move_count < d->best_moves)
				d->best_moves = d->routes_cur->move_count;
			if (d->routes_cur->route_count == d->path_limit)
				break ;
			d->routes_cur = d->routes_cur->next;
			d->rec_counter = 0;
		}
		else if (ret == 3)
		{
			//ft_printf("{yellow}break at route count %d\n", d->routes_cur->route_count);
			d->path_limit = d->routes_cur->route_count;
			break ;
		}
		if (ret == 2 || ret == 0)
		{
			//ft_printf("{green}path_index: %d, route_count: %d\n", d->path_index, d->routes_cur->route_count);
			d->path_index += 1;
			if (d->path_index - 1 == path_stop)
			{
				d->path_limit = d->routes_cur->route_count - 1;
				break ;
			}
		}

			
	}

	// for (int i = 0; i < d->path_index; i++)
	// {
	// 	ft_printf("{green}path %d, steps %d\n", i + 1, d->step_array[i]);
	// 	for (int j = 0; d->paths[i][j] != d->end; j++)
	// 		ft_printf("{red}%s -> ", d->paths[i][j]->name);
	// 	ft_printf("{red}%s -> ", d->end->name);
	// 	ft_printf("\n");
	// }
}

// void	find_more_routes(lem_data *d)
// {
// 	t_room	**route;
// 	t_room	*room;

// 	room = d->end;
// 	d->current = d->end;
// 	route = (t_room **)malloc(sizeof(t_room) * d->path_depth);
// 	if (route == NULL)
// 		exit(1);
// 	recursive_finder(d, route, room, d->path_depth);
// 	d->path_depth += 1;
// 	free(route);
// }

// void	recursive_finder(lem_data *d, t_room **route, t_room *room, int steps)
// {
// 	int	pipe_index;

// 	pipe_index = 0;
// 	while (pipe_index < room->pipe_count)
// 	{
// 		route[steps] = room;
// 		if (room == d->start && steps == 0)
// 			return (save_path(d, route));
// 		if (\
// 		(route[steps] == d->end || route[steps + 1] != room->pipes[pipe_index]))
// 		{
// 			steps--;
// 			if (steps >= 0)
// 			{
// 				room->used = 1;
// 				if (room->pipes[pipe_index]->used != 1)
// 					recursive_finder(d, route, room->pipes[pipe_index], steps);
// 				room->used = -1;
// 			}
// 			steps++;
// 		}
// 		pipe_index++;
// 	}
// }

void print_heat_map(lem_data *d)
{
		for (int i = 0; i < d->map_size; i++)
	{
		for (int j = 0; j < d->map_size; j++)
		{
			if (d->heat_map[i][j] == 0)
				ft_printf("{green}%d ", d->heat_map[i][j]);
			else if (d->heat_map[i][j] == 1)
				ft_printf("{red}%d ", d->heat_map[i][j]);
			else
				ft_printf("%d ", d->heat_map[i][j]);
		}
		ft_printf("\n");
	}
}