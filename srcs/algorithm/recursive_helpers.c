/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:14:25 by ppiirone          #+#    #+#             */
/*   Updated: 2022/12/09 14:14:26 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	init_unique_recursive(lem_data *d)
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

void	dynamic_path_mem_recursive(lem_data *d)
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

int	compare_moves_recursive(lem_data *d)
{
	get_move_counts(d);
	if (d->routes_cur->move_count < d->best_moves)
		d->best_moves = d->routes_cur->move_count;
	if (d->routes_cur->route_count == d->path_limit)
		return (1);
	d->routes_cur = d->routes_cur->next;
		d->rec_counter = 0;
	return (0);
}
