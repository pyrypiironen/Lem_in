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
	d->paths = (t_room ***)malloc(sizeof(t_room **) * PATH_COUNT); // make this dynamic
	d->unique_paths = (t_room ***)malloc(sizeof(t_room **) * d->path_limit);
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
	}


	// Tarkista, onko tarpeeksi uniikkeja
	// Jos ei, niin seuraava leveli
}

int		solution_found(lem_data *d)
{
	if (d->path_index < d->path_limit)
		return (0);
	return (unicorn_finder(d, 0));
}

int		unicorn_finder(lem_data	*d, int	level)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("level (line 71)		%d\n", level);
	if (level == 0)
	{
		d->unique_paths[0] = d->paths[0];
		d->unique_index = 1;
		if (unicorn_finder(d, 1))
			return (1);
	}
	while (i < d->unique_index) //verrataan kasilla olevaa reittia kaikkiin
								//aikaisempiin
	{
		j = level;
		while (j < d->path_index)
		{
			if (is_conflict(d, i, j))
			{
				j++;
				i = 0;
			}
			else
			{
				if (i + 1 == d->unique_index)
				{
					d->unique_paths[d->unique_index] = d->paths[j];
					if (d->unique_index == d->path_limit)
						return (1);
				}
				else if (unicorn_finder(d, level + 1))
						return (1);
				break ;
			}
		}
		i++;
	}
	d->unique_index++;
	return (0);
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