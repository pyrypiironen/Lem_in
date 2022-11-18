/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_found.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:39:02 by ppiirone          #+#    #+#             */
/*   Updated: 2022/10/12 14:39:03 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int	solution_found(lem_data *d)
{
	if (d->path_index == 0)
		return (0);
	fill_heat_map(d);
	return (check_heat_map(d, 0, 0));
}

void	fill_heat_map(lem_data *d)
{
	int	i;

	while (d->path_index >= d->map_size)
		dynamic_heat_map(d);
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
}

void	dynamic_heat_map(lem_data *d)
{
	int	**tmp;
	int	j;

	tmp = d->heat_map;
	j = d->map_size - 1;
	d->map_size += d->map_size;
	d->heat_map = (int **)malloc(sizeof(int *) * d->map_size);
	if (d->heat_map == NULL)
		exit(1);
	copy_heat_map(d, tmp);
	while (j >= 0)
	{
		free(tmp[j]);
		j--;
	}
	free(tmp);
}

void	copy_heat_map(lem_data *d, int **tmp)
{
	int	i;
	int	j;
	int	k;

	i = d->heat_map_index - 1;
	j = 0;
	while (j < d->map_size)
	{
		d->heat_map[j] = (int *)malloc(sizeof(int) * d->map_size);
		if (d->heat_map[j] == NULL)
			exit(1);
		k = 0;
		while (k < d->map_size)
		{
			if (j <= i && k <= i)
				d->heat_map[j][k] = tmp[j][k];
			else
				d->heat_map[j][k] = 2;
			k++;
		}
		j++;
	}
}

int	is_conflict(lem_data *d, int i)
{
	int	j;
	int	k;

	j = 1;
	while (d->paths[d->heat_map_index][j] != d->end)
	{
		k = 1;
		while (d->paths[i][k] != d->end)
		{
			if (d->paths[d->heat_map_index][j] == d->paths[i][k])
				return (1);
			k++;
		}
		j++;
	}
	return (0);
}
