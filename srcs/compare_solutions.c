
#include "../includes/lem_in.h"




void	find_best(lem_data *d)
{
	d->routes_cur = d->routes_head;
	while (1)
	{
		get_move_counts(d);
		if (d->routes_cur->route_count == d->path_limit)
			break ;
		d->routes_cur = d->routes_cur->next;
	}
	
}


void	get_move_counts(lem_data *d)
{
	int	ants;
	int	moves;
	int	i;
	int	steps;

	ants = d->ants;
	moves = d->step_array[d->routes_cur->arr[0]] - 1;
	while (ants > 0)
	{
		i = 0;
		while (i < d->routes_cur->route_count)
		{
			steps = d->step_array[d->routes_cur->arr[i + 1]];
			if (ants < steps || i + 1 == d->routes_cur->route_count)
			{
				ants -= i + 1;
				break ;
			}
			i++;
		}
		//ft_printf("ants: %d, i + 1: %d\n", ants, i + 1);
		moves++;
	}
	d->routes_cur->move_count = moves;
	ft_printf("moves: %d, route_count %d\n", d->routes_cur->move_count, d->routes_cur->route_count);
}