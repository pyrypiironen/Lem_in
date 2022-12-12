/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:10:50 by ppiirone          #+#    #+#             */
/*   Updated: 2022/12/09 15:10:51 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	cleanup(lem_data *d)
{
	int	i;
	int	j;

	i = -1;
	while (++i < d->room_count)
	{
		d->hashmap[i]->parent_a = -1;
		d->hashmap[i]->parent_b = -1;
		d->hashmap[i]->used = 0;
		j = -1;
		while (++j < d->hashmap[i]->pipe_count)
		{
			if (d->hashmap[i]->pipe_flow[j] == 4)
				d->hashmap[i]->used = 2;
			if (d->hashmap[i]->pipe_flow[j] == 4)
				d->hashmap[i]->pipe_flow[j] = 1;
			else if (d->hashmap[i]->pipe_flow[j] == 5)
			{
				d->hashmap[i]->pipe_flow[j] = 2;
				d->hashmap[i]->used = 2;
			}
			else
				d->hashmap[i]->pipe_flow[j] = 0;
		}
	}
}
