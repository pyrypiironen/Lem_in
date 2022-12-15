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
	init_data(d);
	init_routes(d);
	get_floors(d);
	if (d->end->floor == -1)
		print_error();
	get_unique_recursive(d);
	find_best(d);
}

void	dynamic_path_mem(lem_data *d)
{
	t_room	***tmp;
	int		i;

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

	new = 1;
	level = 0;
	d->start->floor = 0;
	while (new)
	{
		d->current = d->head;
		new = get_floors_helper(d, level);
		level++;
	}
}

int	get_floors_helper(lem_data *d, int level)
{
	int	i;
	int	new;

	new = 0;
	while (d->current != NULL)
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
	return (new);
}
