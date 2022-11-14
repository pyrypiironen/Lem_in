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
	check_duplicates(d);
	// Check duplicates
}

void	check_duplicates(lem_data *d)
{
	t_room *tmp;

	d->current = d->head;
	while (d->current)
	{
		tmp = d->current->next;
		while (tmp)
		{
			if (strcmp(d->current->name, tmp->name) == 0)
				print_error();
			tmp = tmp->next;
		}
		check_duplicate_pipes(d);
		d->current = d->current->next;
	}
	d->current = d->head;
}

void	check_duplicate_pipes(lem_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (i < d->current->pipe_count)
	{
		j = i + 1;
		while (j < d->current->pipe_count)
		{
			if (ft_strcmp(d->current->pipes[i]->name, d->current->pipes[j]->name) == 0)
				print_error();
			j++;
		}
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
		{
			free(d->line);
			break ;
		}
		else if (is_valid(d))
			create_room(d);
		else
			print_error();
		free(d->line);
	}
	if (d->start == NULL || d->end == NULL)
		print_error();
}

void	read_pipes(lem_data *d)
{
	while (1)
	{
		if (get_next_line(0, &d->line) == 0 || skip_comments(d) == -1)
			break ;
		if (!is_pipe(d))
			print_error();
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

void	print_error(void)
{
	ft_printf("ERROR\n");
	exit(1);
}

