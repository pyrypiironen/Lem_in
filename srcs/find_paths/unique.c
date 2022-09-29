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
	t_room	**route;
	t_room	*room;



	d->path_depth = d->end->floor;
	d->path_index = 0;
	d->heat_map_index = 0;
	d->paths = (t_room ***)malloc(sizeof(t_room **) * PATH_COUNT); // make this dynamic
	// check mallocs
	
	while (!solution_found(d))
	{
		room = d->end;
		d->current = d->end;
		route = (t_room **)malloc(sizeof(t_room) * d->path_depth);
		// check malloc
		recursive_finder(d, route, room, d->path_depth);
		d->path_depth += 1;
		free(route);
		if (d->path_depth == 42)
			break ;
	}


	// Tarkista, onko tarpeeksi uniikkeja
	// Jos ei, niin seuraava leveli
}

int		solution_found(lem_data *d)
{
	// if (d->heat_map_index == 0)
	// 	return (0);
	// lue nykyinen taso heat_mappiin
	fill_heat_map(d);
	return (0);

	// tarkista löytyikö ratkaisu


}

void	fill_heat_map(lem_data *d)
{
	int	i;



	while (d->heat_map_index < d->path_index)
	{
		i = 0;
		while (i < d->heat_map_index)
		{
			d->heat_map[d->heat_map_index][i] = is_conflict(d, i);
			i++;
		}
		d->heat_map_index += 1;
	}

	ft_printf("path_index: %d\n", d->path_index);
	for (int k = 0; k < 20; k++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (d->heat_map[k][j] == 2)
				ft_printf(" %d ", d->heat_map[k][j]);
			else
				ft_printf("{green} %d ", d->heat_map[k][j]);
		}
			
		ft_printf("\n");
	}
}

int		is_conflict(lem_data *d, int i)
{
	i = 1;

	(void)d;
	return i;
}


void	recursive_finder(lem_data *d, t_room **route, t_room *room, int steps)
{
	int	pipe_index;

	pipe_index = 0;
	while (pipe_index < room->pipe_count)
	{
		route[steps] = room;
		if (room == d->start && steps == 0) 
		{
			save_path(d, route);
			return ;
		}
		
		if (room->floor >= room->pipes[pipe_index]->floor && (route[steps] == d->end || route[steps + 1] != room->pipes[pipe_index]))
		{
			steps--;
			if (steps >= 0)
				recursive_finder(d, route, room->pipes[pipe_index], steps);
			steps++;
		}
		pipe_index++;
	}
}