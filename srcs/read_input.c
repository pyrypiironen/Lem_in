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
	*str	line;
	
	read_ants(d);
	// First while loop to read rooms.
	while (1)
	{
		get_next_line(0, &d->line);
		skip_comments(d);
		if (check_start_end(d));
			continue ;
		else if (is_pipe)
			break ;
		else if (is_valid())
			create_room(d);
		else
			exit(0); 			// Add error message here!
		free(line);
	}
	// Next while loop to read pipes
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

int		check_start_end(lem_data *d)
{
	int	ret;

	ret = 0;
	// If line is "##start", get_next_line and save it to d->start;
	if (ft_strcmp(d->line, "##start") == 0)
	{
		free(d->line);
		get_next_line(0, d->line);
		skip_comments(d);
		create_room(*d, d->line);
		d->start = d->current;
		ret = 1;
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		free(d->line);
		get_next_line(0, d->line);
		skip_comments(d);
		create_room(*d, d->line);
		d->end = d->current;
		ret = 1;
	}
	return (ret);
}


void	create_room(lem_data *d, char *str)
{
	int i;
	// d->head yms pitää alustaa nulleiksi, kun lem_data luodaan.

	// If head is null, there is not a single room, and new room will be created
	// to d->current and is the head. Else new room will be created to
	//	d->current->next. After this function, d->current is last created room.
	if (d->head != NULL)
		d->current = d->current->next;
	d->current = (s_room *)malloc(sizeof(s_room));
	if (d->head == NULL)
		d->head = d->current;
	// Save the name and coordinates to node s_room.
	while (str[i] != ' ')
		d->current->name[i] = str[i++];
	d->current->name[i] = '\0';
	d->current->x = lem_atoi(str[i + 1]);
	i++;
	while (str[i] != ' ')
		i++;
	d->current->y = lem_atoi(str[i + 1]);
	// Nyt menee läpi myö rivit, jossa on ylimääräistä tavaraa koordinaattien
	// perässä. Luo error check.
}

int		skip_comments(lem_data *d)
{
	int	ret;

	ret = 0;
	while (d->line[0] == '#' && ft_strcmp(d->line, "##start") != 0 \
		&& ft_strcmp(d->line, "##end") != 0);
	{
		free(d->line;
		get_next_line(o, &d->line);
		ret = 1;
	}
	return (ret);
}
