/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjokela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:35:42 by mjokela           #+#    #+#             */
/*   Updated: 2022/11/17 14:35:44 by mjokela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	check_duplicates(lem_data *d)
{
	t_room	*tmp;

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
			if (ft_strcmp(d->current->pipes[i]->name, \
			d->current->pipes[j]->name) == 0)
				print_error();
			j++;
		}
		i++;
	}
}

void	check_one_step_solution(lem_data *d)
{
	int	i;

	i = 0;
	while (i < d->start->pipe_count)
	{
		if (d->start->pipes[i] == d->end)
			print_super_solution(d);
		i++;
	}
}

int	check_start_end(lem_data *d)
{
	if (ft_strcmp(d->line, "##start") == 0)
	{
		lem_to_print(d);
		free(d->line);
		get_next_line(0, &d->line);
		if (skip_comments(d) == 1 || !is_valid(d) || d->start != NULL)
			print_error();
		create_room(d);
		d->start = d->current;
		return (1);
	}
	else if (ft_strcmp(d->line, "##end") == 0)
	{
		lem_to_print(d);
		free(d->line);
		get_next_line(0, &d->line);
		if (skip_comments(d) == 1 || !is_valid(d) || d->end != NULL)
			print_error();
		create_room(d);
		d->end = d->current;
		return (1);
	}
	return (0);
}
