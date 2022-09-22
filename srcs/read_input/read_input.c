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

#include "../../includes/lem_in.h"

void	input(lem_data *d)
{
	d->head = NULL;
	d->current = NULL;
	d->start = NULL;
	d->end = NULL;
	// Check if line start with 'L'
	read_ants(d);
	read_rooms(d);
	read_pipes(d);
	// Check duplicates
}

void	read_ants(lem_data *d)
{
	char *str;

	get_next_line(0, &str);
	d->ants = lem_atoi(str);
	free(str);
	if (d->ants < 0 || d->ants > 2147483647)
		exit(0);			// Add error message here!
}

void	read_rooms(lem_data *d)
{
	while (1)
	{
		get_next_line(0, &d->line);
		if (check_start_end(d))
			;
		else if (is_pipe(d))
		{
			free(d->line);
			break ;
		}

		else if (is_valid(d))
			create_room(d);
		else if (skip_comments(d) == 0)
		{
			ft_printf("error\n");
			exit(0); 			// Add error message here!
		}
		free(d->line);
	}
	if (d->start == NULL || d->end == NULL)
		exit(0); 				// Add error message here!
}

void	read_pipes(lem_data *d)
{
	while (1)
	{
		if (get_next_line(0, &d->line) == 0 || skip_comments(d) == -1)
			break ;
		if (!is_pipe(d))
		{
			ft_printf("errori\n"); // Clean error message
			exit(1);
		}
		free(d->line);
	}
}

int		skip_comments(lem_data *d)
{
	int	ret;

	ret = 0;
	while (ft_strncmp(d->line, "#", 1) == 0 && \
		ft_strcmp(d->line, "##start") != 0 && ft_strcmp(d->line, "##end") != 0)
	{
		free(d->line);
		if (get_next_line(0, &d->line) == 0)
			return (-1);
		ret = 1;
	}
	return (ret);
}


