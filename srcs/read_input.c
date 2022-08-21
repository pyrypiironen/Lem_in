/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:52:52 by ppiirone          #+#    #+#             */
/*   Updated: 2022/08/21 14:52:53 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	input(lem_data *d)
{
	read_ants(d);
	read_rooms(argv, d);
}

void	read_ants(lem_data *d)
{
	char	*str;

	get_next_line(0, &str);
	d->ants = lem_atoi(str);
	if (d->ants < 0 || d->ants > 2147483647)
		exit(0);			// Add error message here!
	ft_printf("Ants = %d\n", d->ants);		// Delete!

	free(str);
}

void	read_rooms(lem_data *d)
{
	char	*str;

	while (1)
	{
		get_next_line(0, &str);
		if (ft_strcmp(str, "##start") == 0)
			break;
		if (strncmp(str, "#", 1) != 0)
			exit(0);		// Add error message here! And free!
		free(str);
	}
	free(str);
	while (1)
	{
		get_next_line(0, &str);



		free(str);
	}

}

if start
if end
if comment
if pipe -> break ;
is valid