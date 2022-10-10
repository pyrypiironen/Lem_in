
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
	int min_moves;

	ants = d->ants;
	min_moves = 0;
	moves = 0; //d->step_array[d->routes_cur->arr[0]] - 1;
	while (ants > 0)
	{
		i = 0;
		while (i < d->routes_cur->route_count)
		{
			steps = d->step_array[d->routes_cur->arr[i + 1]] - d->step_array[d->routes_cur->arr[i]];
			if (ants / (i + 1) <= steps || ants == i + 1 || i + 1 == d->routes_cur->route_count)
			{
				if (i + 1 != d->routes_cur->route_count && steps == 0)
					i++;
				ants -= i + 1;
				if (min_moves < moves + d->step_array[d->routes_cur->arr[i]])
					min_moves = moves + d->step_array[d->routes_cur->arr[i]];
				break ;
			}
			i++;
		}
		ft_printf("ants: %d, i + 1: %d\n", ants, i + 1);
		moves++;
	}
	moves += d->step_array[d->routes_cur->arr[0]] - 1;
	if (min_moves > moves)
		moves = min_moves;
	d->routes_cur->move_count = moves;
	ft_printf("moves: %d, route_count %d\n", d->routes_cur->move_count, d->routes_cur->route_count);
}