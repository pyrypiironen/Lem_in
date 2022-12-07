#include "../../includes/lem_in.h"

void	cleanup(lem_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (i < d->room_count)
	{
		d->hashmap[i]->parent_a = -1;
		d->hashmap[i]->parent_b = -1;
		d->hashmap[i]->used = 0;
		j = 0;
		while (j < d->hashmap[i]->pipe_count)
		{
			// if (d->hashmap[i]->pipe_flow[j] < 4)
			// 	d->hashmap[i]->pipe_flow[j] = 0;
			if (d->hashmap[i]->pipe_flow[j] == 4)
			{
				d->hashmap[i]->pipe_flow[j] = 1;
				d->hashmap[i]->used = 2;
			}
			else if (d->hashmap[i]->pipe_flow[j] == 5)
			{
				d->hashmap[i]->pipe_flow[j] = 2;
				d->hashmap[i]->used = 2;
			}
			else
				d->hashmap[i]->pipe_flow[j] = 0;
			j++;
		}
		i++;
	}

}