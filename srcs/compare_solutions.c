
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
	//ft_printf("ants: %d\n", ants);
	moves = d->step_array[d->routes_cur->arr[0]] - 1;
	//ft_printf("init moves: %d\n", moves);
	while (ants > 0)
	{
		i = 0;
		//steps = d->step_array[d->routes_cur->arr[0]];
		while (i < d->routes_cur->route_count)
		{
			//ft_printf("ants: %d, steps: %d\n", ants, steps);
			//sleep(1);
				
			if (ants < d->step_array[d->routes_cur->arr[i + 1]] || i + 1 == d->routes_cur->route_count)
			{
				// if (steps == 17)
				// 	i--;
				ants -= i + 1;
				break ;
			}
			// if (ants <= steps + d->step_array[d->routes_cur->arr[i + 1]])
			// {
			// 	//ft_printf("ants: %d\n", ants);
			// 	ants -= i + 1;
			// 	break ;
			// }
			i++;
			// if (i != d->routes_cur->route_count)
			// 	steps += d->step_array[d->routes_cur->arr[i]];

		}
		ft_printf("ants: %d, i + 1: %d, steps: %d\n", ants, i + 1, steps);
		moves++;
	}
	d->routes_cur->move_count = moves;
	ft_printf("moves: %d, route_count %d\n", d->routes_cur->move_count, d->routes_cur->route_count);
	
	
}