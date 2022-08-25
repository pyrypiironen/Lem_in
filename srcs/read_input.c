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
	read_rooms(d);
	// read_pipes(d);
	
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
	while (1)
	{
		get_next_line(0, &d->line);
		if (check_start_end(d));
			continue ;
		else if (is_pipe(d))
			break ;
		else if (is_valid())
			create_room(d);
		else if (skip_comments(d) == 0)
			exit(0); 			// Add error message here!
		free(line);
	}
	if (d->start == NULL || d->end == NULL)
		exit(0); 				// Add error message here!
}



int		skip_comments(lem_data *d)
{
	int	ret;

	ret = 0;
	while (ft_strncmp(d->line, "#", 1) == 0 && \
		ft_strcmp(d->line, "##start") != 0 && ft_strcmp(d->line, "##end") != 0);
	{
		free(d->line);
		get_next_line(0, &d->line);
		ret = 1;
	}
	return (ret);
}

