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
	read_ants(d);
	read_rooms(d);
	read_pipes(d);
	check_duplicates(d);
	check_one_step_solution(d);
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

void	print_super_solution(lem_data *d)
{
	int	i;

	i = 1;
	while (i <= d->ants)
	{
		ft_printf("L%d-%s", i, d->end->name);
		if (i < d->ants)
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
	exit(0);
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
		{
			free(d->line);
			break ;
		}
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

void	lem_to_print(lem_data *d)
{
	lem_print *new;

	new = (lem_print *)malloc(sizeof(lem_print));
	if (new == NULL)
		exit(1);
	new->str = ft_strdup(d->line);
	new->next = NULL;
	if (d->print_head == NULL)
	{
		d->print_head = new;
		d->print_current = d->print_head;
	}
	else
	{
		d->print_current->next = new;
		d->print_current = d->print_current->next;
	}
}
