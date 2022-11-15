
#include "../includes/lem_in.h"




void	find_best(lem_data *d)
{
	d->routes_head->move_count = 2147483647;
	d->routes_best = d->routes_head;
	d->routes_cur = d->routes_head;
	while (1)
	{
		get_move_counts(d);
		if (d->routes_cur->move_count < d->routes_best->move_count)
			d->routes_best = d->routes_cur;
		if (d->routes_cur->route_count == d->path_limit)
			break ;
		d->routes_cur = d->routes_cur->next;

	}
	//ft_printf("BEST, moves: %d, route_count %d\n", d->routes_best->move_count, d->routes_best->route_count);
	//ft_printf("BEST, route 1 %d, route 2 %d\n", d->routes_best->arr[0], d->routes_best->arr[1]);

	
}


// UUSI
void	get_move_counts(lem_data *d)
{
	int	ants;
	int	i;
	int value_array[10000];

	i = 0;
	ants = d->ants;
	while (i < d->routes_cur->route_count)
	{
		value_array[i] = d->step_array[d->routes_cur->arr[i]];
		i++;

	}
	while (ants > 0)
	{
		i = d->routes_cur->route_count - 1;
		while (value_array[i - 1] <= value_array[i] && i >= 1)
			i--;
		value_array[i] += 1;
		ants--;
	}
	i = 0;
	d->routes_cur->move_count = value_array[d->routes_cur->route_count - 1] - 1;
	while (i < d->routes_cur->route_count)
	{
		if (value_array[i] - 1 > d->routes_cur->move_count)
			d->routes_cur->move_count = value_array[i] - 1;
		i++;
	}
	//ft_printf("moves: %d, route_count %d\n", d->routes_cur->move_count, d->routes_cur->route_count);
}



// VANHA
// void	get_move_counts(lem_data *d)
// {
// 	int	ants;
// 	int	moves;
// 	int	i;
// 	int	steps;
// 	int min_moves;

// 	ants = d->ants;
// 	min_moves = 0;
// 	moves = 0; //d->step_array[d->routes_cur->arr[0]] - 1;
// 	while (ants > 0)
// 	{
// 		i = 0;
// 		while (i < d->routes_cur->route_count)
// 		{
// 			steps = d->step_array[d->routes_cur->arr[i + 1]] - d->step_array[d->routes_cur->arr[i]];
// 			if (ants / (i + 1) <= steps || ants == i + 1 || i + 1 == d->routes_cur->route_count)
// 			{
// 				if (i + 1 != d->routes_cur->route_count && steps == 0)
// 					i++;
// 				ants -= i + 1;
// 				if (min_moves < moves + d->step_array[d->routes_cur->arr[i]])
// 					min_moves = moves + d->step_array[d->routes_cur->arr[i]];
// 				break ;
// 			}
// 			i++;
// 		}
// 		//ft_printf("ants: %d, i + 1: %d\n", ants, i + 1);
// 		moves++;
// 	}
// 	moves += d->step_array[d->routes_cur->arr[0]] - 1;
// 	if (min_moves > moves)
// 		moves = min_moves;
// 	d->routes_cur->move_count = moves;
// 	ft_printf("moves: %d, route_count %d\n", d->routes_cur->move_count, d->routes_cur->route_count);
// }