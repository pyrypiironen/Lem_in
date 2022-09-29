/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:04:28 by ppiirone          #+#    #+#             */
/*   Updated: 2022/09/21 19:04:31 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	solve_paths(lem_data *d)
{
	int i = 0;
	d->path_limit = d->start->pipe_count;
	if (d->end->pipe_count < d->path_limit)
		d->path_limit = d->end->pipe_count;
	if (d->path_limit > d->ants)
		d->path_limit = d->ants;
	d->heat_map = (int **)malloc(sizeof(int *) * 100);
	while (i < 100)
	{
		d->heat_map[i] = (int *)malloc(sizeof(int) * 100);
		i++;
	}
	for (int k = 0; k < 100; k++)   // helper => remove
	{
		for (int j = 0; j < 100; j++)
			d->heat_map[k][j] = 2;
	}
	get_floors(d);
	get_unique(d);
	// Etsi parhaat reitit


}



void	save_path(lem_data *d, t_room **route)
{
	int	i;

	i = 0;
	d->paths[d->path_index] = (t_room **)malloc(sizeof(t_room) * d->path_depth);
	// malloc check

	while (i <= d->path_depth)
	{
		d->paths[d->path_index][i] = route[i];
		i++;
	}
	d->path_index += 1; // tarkista tarviiko dynaamisesti allokoida tilaa
}

void	get_floors(lem_data *d)
{
	int	new;
	int	level;
	int	i;

	new = 1;
	level = 0;
	d->start->floor = 0;
	while (new)
	{
		d->current = d->head;
		new = 0;
		while (d->current->next != NULL)
		{
			if (d->current->floor == level)
			{
				i = 0;
				while (i < d->current->pipe_count)
				{
					if (d->current->pipes[i]->floor == -1)
					{
						d->current->pipes[i]->floor = level + 1;
						new = 1;
					}
					i++;
				}
			}
			d->current = d->current->next;
		}
		level++;
	}
}
