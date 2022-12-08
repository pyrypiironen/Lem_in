/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjokela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:38:02 by mjokela           #+#    #+#             */
/*   Updated: 2022/11/17 16:38:07 by mjokela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int	check_heat_map(lem_data *d, int nb, int in)
{
	


	int	ret;

	if (d->rec_counter++ > 3000000)
	{
		
		return (3);
	}
	while (1)
	{
		while (!compare_array(d, nb, in))
			if (nb++ >= d->path_index)
				return (0);
		d->array[in] = nb;
		if (in == 9999)
			return (3);
		if (in + 1 == d->routes_cur->route_count)
			return (fill_route_array(d));
		if (nb + 1 == d->path_index)
			return (2);
		ret = check_heat_map(d, nb + 1, in + 1);
		if (ret != 0)
			return (ret);
		nb++;
	}
}

int	fill_route_array(lem_data *d)
{
	int	i;
	//int	k;

	i = 0;
	//k = 0;
	d->max_route_count = d->routes_cur->route_count;
	//ft_printf("{purple}route_count: %d\n", d->routes_cur->route_count);
	while (i < d->routes_cur->route_count)
	{
		// ONLY PRINT
		// for (int j = 0; d->paths[d->array[i]][j] != d->end; j++)
		// 	ft_printf("{red}%s -> ", d->paths[d->array[i]][j]->name);
		// ft_printf("{red}%s\n", d->end->name);
		//Indeksit uniikeille reiteille:
		//ft_printf("{cyan}i: %d", d->array[i]);
		d->routes_cur->arr[i] = d->array[i];
		i++;
	}
	//sleep(5);
	// while (k < d->routes_cur->route_count)
	// 	k++;
	return (1);
}

int	compare_array(lem_data *d, int nb, int in)
{
	//ft_printf("{green}fill_route_array IN, routes: %d, in: %d, nd: %d\n", d->path_index, in, nb);
	int	i;

	i = 0;
	while (i < in)
	{
		if (d->heat_map[nb][d->array[i]] != 0)
		{
			//	ft_printf("{red}fill_route_array OUT 0\n");
				return (0);
		}
			
		i++;
	}
	//ft_printf("{red}fill_route_array OUT 1\n");
	return (1);
}
