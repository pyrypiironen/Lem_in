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
	d->room_count = 0;
	read_ants(d);
	read_rooms(d);
	read_pipes(d);
	check_duplicates(d);
	check_one_step_solution(d);
	create_room_array(d);
}

void	create_room_array(lem_data *d)
{
	int	i;

	i = 0;
	d->current = d->head;
	d->hashmap = (t_room **)malloc(sizeof(t_room *) * d->room_count);
	d->bfs_rooms = (int *)malloc(sizeof(int) * d->room_count);
	d->bfs_copy = (int *)malloc(sizeof(int) * d->room_count);
	if (d->hashmap == NULL || d->bfs_rooms == NULL || d->bfs_copy == NULL)
		print_error();
	while (i < d->room_count)
	{
		d->current->pipe_flow = (int *)malloc(sizeof(int) * \
			d->current->pipe_count);
		if (d->current->pipe_flow == NULL)
			print_error();
		d->hashmap[i] = d->current;
		d->current = d->current->next;
		i++;
	}
}

void	read_ants(lem_data *d)
{
	get_next_line(0, &d->line);
	if (!d->line)
		print_error();
	skip_comments(d);
	d->ants = lem_atoi(d->line);
	d->print_head = NULL;
	lem_to_print(d);
	free(d->line);
	if (d->ants < 0)
		print_error();
}

void	read_rooms(lem_data *d)
{
	while (1)
	{
		if (get_next_line(0, &d->line) == 0)
			print_error();
		skip_comments(d);
		if (check_start_end(d))
			;
		else if (is_pipe(d))
			break ;
		else if (is_valid(d))
			create_room(d);
		else
			print_error();
		lem_to_print(d);
		free(d->line);
	}
	if (d->start == NULL || d->end == NULL)
		print_error();
}

void	read_pipes(lem_data *d)
{
	while (1)
	{
		lem_to_print(d);
		free(d->line);
		if (get_next_line(0, &d->line) == 0 || skip_comments(d) == -1)
			break ;
		if (!is_pipe(d))
			print_error();
	}
}

int	skip_comments(lem_data *d)
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
