/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjokela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:27:18 by mjokela           #+#    #+#             */
/*   Updated: 2022/11/17 15:27:22 by mjokela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	send_ants(lem_data *d)
{
	int		ants;
	t_room	***best_paths;
	int		i;

	ants = d->ants;
	i = 0;
	d->start->ant_nbr = 1;
	d->best_route_count = d->routes_best->route_count;
	best_paths = (t_room ***)malloc(sizeof(t_room **) * \
	d->routes_best->route_count);
	d->best_steps = (int *)malloc(sizeof(int) * d->routes_best->route_count);
	if (best_paths == NULL || d->best_steps == NULL)
		exit (1);
	while (i < d->routes_best->route_count)
	{
		best_paths[i] = d->paths[d->routes_best->arr[i]];
		d->best_steps[i] = d->step_array[d->routes_best->arr[i]];
		i++;
	}
	while (d->end->ant_nbr < ants)
		move_ants(d, best_paths);
}

void	move_ants(lem_data *d, t_room ***best_paths)
{
	int	i;
	int	j;

	i = 0;
	d->space = 0;
	while (i < d->best_route_count)
	{
		j = d->best_steps[i] - 1;
		while (j >= 0)
		{
			if (best_paths[i][j]->ant_nbr != 0)
				move_ant(d, best_paths, i, j);
			j--;
		}
		i++;
	}
	ft_printf("\n");
	d->routes_best->move_count -= 1;
	while (d->routes_best->move_count < \
	d->best_steps[d->routes_best->route_count - 1])
		d->routes_best->route_count -= 1;
}

void	move_ant(lem_data *d, t_room ***best_paths, int i, int j)
{
	int	ant_number;

	ant_number = best_paths[i][j]->ant_nbr;
	if (i >= d->routes_best->route_count && j == 0)
		return ;
	if (j + 1 == d->best_steps[i])
		d->end->ant_nbr += 1;
	else
		best_paths[i][j + 1]->ant_nbr = best_paths[i][j]->ant_nbr;
	if (j != 0)
		best_paths[i][j]->ant_nbr = 0;
	else if (d->start->ant_nbr == d->ants)
		d->start->ant_nbr = 0;
	else
		d->start->ant_nbr += 1;
	if (d->space)
		ft_printf(" ");
	d->space = 1;
	ft_printf("L%d-%s", ant_number, best_paths[i][j + 1]->name);
}
