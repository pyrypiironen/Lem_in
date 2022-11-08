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

int		solution_found(lem_data *d)
{
	if (d->path_index == 0)
		return (0);
	// Lue nykyinen taso heat_mappiin.
	
	fill_heat_map(d);
	// Tarkista löytyikö ratkaisu ja palauta totuusarvo.
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
	// ft_printf("map_size: %d\n", d->map_size);
	// ft_printf("path_index: %d\n", d->path_index);
	// for (int k = 0; k <= d->path_index; k++)
	// {
	// 	for (int j = 0; j <= d->path_index; j++)
	// 	{
	// 		if (d->heat_map[k][j] == 2)
	// 			ft_printf(" %d ", d->heat_map[k][j]);
	// 		else if (d->heat_map[k][j] == 0)
	// 			ft_printf("{green} %d ", d->heat_map[k][j]);
	// 		else
	// 			ft_printf("{red} %d ", d->heat_map[k][j]);
	// 	}
			
	// 	ft_printf("\n");
	// }
}

void	dynamic_heat_map(lem_data *d)
{
	int	**tmp;
	int	i;
	int	j;
	int	k;

	
	i = d->heat_map_index - 1;
	j = 0;
	tmp = d->heat_map;
	d->map_size += d->map_size;
	d->heat_map = (int **)malloc(sizeof(int *) * d->map_size);
	if (d->heat_map == NULL)
		exit(1);
	while (j < d->map_size)
	{
		d->heat_map[j] = (int *)malloc(sizeof(int) * d->map_size);
		k = 0;
		while (k < d->map_size)
		{
			if (j <= i && k <= i)
				d->heat_map[j][k] = tmp[j][k];
			else
				d->heat_map[j][k] = 2;
			k++;
		}
		if (j <= i)
			free(tmp[j]);
		j++;
	}
	free(tmp);
}

int		is_conflict(lem_data *d, int i)
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


// // nb == heat_mapin rivi / pathsin reitin indeksi, in == indeksi reitti arrayssa (uniikit kombot)
// int	check_heat_map(lem_data *d, int nb, int in) // Eka kutsu in = 0; nb 0;
// {
// 	while (1)
// 	{
// 		while (!compare_array(d, nb, in))
// 		{
// 			nb++;
// 			if (nb == d->path_index) //ei loytynyt ei-konfliktaavaa reittia
// 			{
// 				d->rec_counter += 1;
// 				return (0);
// 			}
				
// 		}
// 		//ft_printf("cur: %d, total: %d\n", d->current_steps, d->total_steps);

// 		d->array[in] = nb;
// 		update_current_steps(d, in);
		
// 		sleep(1);
// 		if (d->current_steps >= d->total_steps)
// 			return (0);
// 		if (in + 1 == d->routes_cur->route_count)
// 		{
// 			if (d->current_steps < d->total_steps)
// 				fill_route_array(d);
// 		}
			
// 		if (in + 1 == d->path_limit)
// 		{
// 			// int k = 0;
// 			// while (k < d->path_limit)
// 			// {
// 			// 	ft_printf("{yellow}here %i \n", d->array[k]);
// 			// 	k++;
// 			// }
// 			//ft_printf("{yellow} return check_heat_map (0)\n");
// 			return (1);// oli return 1
// 		}
// 		if (nb + 1  == d->path_index)
// 		{	
// 			//d->total_steps = 2147483647;
// 			return (0);
// 		}
// 		ft_printf("cur: %d, total: %d\n", d->current_steps, d->total_steps);
// 		if (check_heat_map(d, nb + 1, in + 1) == 1)
// 			return (1);
// 		nb++;
// 		// if (nb == d->path_index)
// 		// {
// 		// 	//ft_printf("{yellow} return check_heat_map (1)\n");
// 		// 	return (1);
// 		// }
			
// 	}
	
// 	return (-1);
// }

void	update_current_steps(lem_data *d, int in)
{
	d->current_steps = 0;
	while (in >= 0)
	{
		d->current_steps += d->step_array[d->array[in]];
		//ft_printf("steps: %d\n", d->step_array[d->array[in]]);
		//sleep(1);
		in--;
	}
	
}
