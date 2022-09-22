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
	d->path_limit = d->start->pipe_count;
	if (d->end->pipe_count < d->path_limit)
		d->path_limit = d->end->pipe_count;
	if (d->path_limit > d->ants)
		d->path_limit = d->ants;
	get_floors(d);
	get_unique(d);
	// Etsi parhaat reitit


}

int		is_conflict(lem_data *d, int i, int j)
{
	int	k;
	int	m;
	ft_printf("Is_conflict (line 113) | i = %d | j = %d\n", i, j);
	k = 1;
	while (d->unique_paths[i] != NULL && d->unique_paths[i][k] != d->end)
	{
		m = 1;
		// ft_printf("current %p %s\n", d->unique_paths[i][k], d->unique_paths[i][k]->name);
		// ft_printf("end %p %s\n", d->end, d->end->name);
		//ft_printf("k %d\n", k);
		while (d->paths[j][m] != d->end)
		{
			// ft_printf("current %p %s\n", d->paths[j][m], d->paths[j][m]->name);
			// ft_printf("end %p %s\n", d->end, d->end->name);
			//ft_printf("m %d\n", m);
			if (d->unique_paths[i][k] == d->paths[j][m])
			{
				ft_printf("Is_conflict return (1);\n");
				return (1);
			}
			m++;
		}
		k++;
		// ft_printf("current %p %s\n", d->unique_paths[i][k], d->unique_paths[i][k]->name);
		// ft_printf("end %p %s\n", d->end, d->end->name);
	}
	ft_printf("Is_conflict return (0);\n");
	return (0);
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
