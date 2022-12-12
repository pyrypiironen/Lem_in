/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjokela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:36:17 by mjokela           #+#    #+#             */
/*   Updated: 2022/11/15 14:48:29 by mjokela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	init_data(lem_data *d)
{
	int	i;

	i = 0;
	d->path_mem = 42;
	d->map_size = 42;
	d->rec_counter = 0;
	d->path_limit = d->start->pipe_count;
	if (d->end->pipe_count < d->path_limit)
		d->path_limit = d->end->pipe_count;
	if (d->path_limit > d->ants)
		d->path_limit = d->ants;
	d->route = (t_room **)malloc(sizeof(t_room *) * d->room_count);
	d->heat_map = (int **)malloc(sizeof(int *) * d->map_size);
	if (d->route == NULL || d->heat_map == NULL)
		exit (1);
	while (i < d->map_size)
	{
		d->heat_map[i] = (int *)malloc(sizeof(int) * d->map_size);
		if (d->heat_map[i] == NULL)
			exit (1);
		i++;
	}
	init_heat_map(d);
}

void	init_routes(lem_data *d)
{
	int	i;

	i = 1;
	d->routes_cur = (routes *)malloc(sizeof(routes));
	if (d->routes_cur == NULL)
		exit (1);
	d->routes_head = d->routes_cur;
	d->routes_cur->route_count = 1;
	while (i < d->path_limit)
	{
		d->routes_cur->next = (routes *)malloc(sizeof(routes));
		if (d->routes_cur->next == NULL)
			exit (1);
		d->routes_cur = d->routes_cur->next;
		d->routes_cur->route_count = i + 1;
		i++;
	}
	d->routes_cur = d->routes_head;
	d->routes_best = d->routes_head;
}

void	init_heat_map(lem_data *d)
{
	int	k;
	int	j;

	k = 0;
	while (k < d->map_size)
	{
		j = 0;
		while (j < d->map_size)
		{
			d->heat_map[k][j] = 2;
			j++;
		}
		k++;
	}
}

void	init_unique(lem_data *d)
{
	int	i;

	i = 0;
	d->path_depth = d->end->floor;
	d->path_index = 0;
	d->heat_map_index = 0;
	d->best_moves = 2147483647;
	while (i < 10000)
		d->array[i++] = 2147483647;
	d->paths = (t_room ***)malloc(sizeof(t_room **) * d->path_mem);
	if (d->paths == NULL)
		exit(1);
}

int	compare_moves(lem_data *d, int ret)
{
	if (ret == 1)
	{
		get_move_counts(d);
		if (d->routes_cur->move_count < d->best_moves)
			d->best_moves = d->routes_cur->move_count;
		if (d->routes_cur->route_count == d->path_limit)
			return (1);
		d->routes_cur = d->routes_cur->next;
		d->rec_counter = 0;
	}
	else if (ret == 3)
	{
		d->path_limit = d->routes_cur->route_count;
		return (1);
	}
	return (0);
}
