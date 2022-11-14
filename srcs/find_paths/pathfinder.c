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
	int i;
	
	i = 0;

	d->path_mem = 42;
	d->map_size = 2;		// fix size to final version
	d->rec_counter = 0;
	d->path_limit = d->start->pipe_count;
	if (d->end->pipe_count < d->path_limit)
		d->path_limit = d->end->pipe_count;
	if (d->path_limit > d->ants)
		d->path_limit = d->ants;
	d->heat_map = (int **)malloc(sizeof(int *) * d->map_size);
	if (d->heat_map == NULL)
		exit (1);
	while (i < d->map_size)
	{
		d->heat_map[i] = (int *)malloc(sizeof(int) * d->map_size);
		if (d->heat_map[i] == NULL)
			exit (1);
		i++;
	}
	for (int k = 0; k < d->map_size; k++) // for loopit pois
	{
		for (int j = 0; j < d->map_size; j++)
			d->heat_map[k][j] = 2;
	}
	init_routes(d);
	get_floors(d);
	if (d->end->floor == -1)
		print_error();
	get_unique(d);
	find_best(d);
	

	// Etsi parhaat reitit


}



void	save_path(lem_data *d, t_room **route)
{
	int	i;

	i = 0;
	d->paths[d->path_index] = (t_room **)malloc(sizeof(t_room) * d->path_depth);
	if (d->paths == NULL)
		exit(1);
	d->step_array[d->path_index] = d->path_depth;
	while (i <= d->path_depth)
	{
		d->paths[d->path_index][i] = route[i];
		i++;
	}
	d->path_index += 1;
	if (d->path_index == d->path_mem)
		dynamic_path_mem(d); // Ei toimmi
}

void	dynamic_path_mem(lem_data *d)
{
	t_room	***tmp;
	int		i;

	//ft_printf("{red}Dynamic paths | d->path index = %i | \n", d->path_index);

	i = d->path_index - 1;
	tmp = d->paths;
	d->path_mem += d->path_mem;
	d->paths = (t_room ***)malloc(sizeof(t_room **) * d->path_mem);
	if (d->paths == NULL)
		exit(1);
	while (i >= 0)
	{
		d->paths[i] = tmp[i];
		i--;
	}
	free(tmp);
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
