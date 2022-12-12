/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:53:43 by ppiirone          #+#    #+#             */
/*   Updated: 2022/12/12 13:53:45 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	overwrite_paths(lem_data *d)
{
	int	i;

	i = 0;
	while (i < d->path_index)
	{
		d->paths[i] = d->sorted_paths[i];
		d->step_array[i] = d->sorted_steps[i];
		i++;
	}	
}

void	overwrite_sorted(lem_data *d, int current, int max)
{
	int	i;
	int	j;

	j = 0;
	while (current <= max)
	{
		i = 0;
		while (i < d->path_index)
		{
			if (d->step_array[i] == current)
			{
				d->sorted_paths[j] = d->paths[i];
				d->sorted_steps[j] = d->step_array[i];
				j++;
			}
			i++;
		}
		current++;
	}
}
