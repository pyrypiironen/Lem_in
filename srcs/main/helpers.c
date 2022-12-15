/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:24:59 by ppiirone          #+#    #+#             */
/*   Updated: 2022/12/09 13:25:00 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	copy_input(lem_data *f, lem_data *d)
{
	d->head = f->head;
	d->current = f->current;
	d->start = f->start;
	d->end = f->end;
	d->ants = f->ants;
	d->path_limit = f->path_limit;
	d->route = f->route;
	d->room_count = f->room_count;
}

void	t_flag(lem_data *d, lem_data *f)
{
	ft_printf("{yellow}>>>> >>>> >>>> Test results: <<<< <<<< <<<<\n\n");
	ft_printf("Number of rooms: %d\n", f->room_count);
	ft_printf("Number of ants:  %d\n\n", f->ants);
	ft_printf("Result with flow: %7d\n", f->best_moves);
	ft_printf("Result with recursive: %d\n\n", d->best_moves);
	if (f->best_moves < d->best_moves)
		d->best_moves = f->best_moves;
	ft_printf("{green}Lem-in best result: %21d\n", d->best_moves);
	ft_printf("{blue}#Here is the number of lines required: %d\n\n", \
	f->optimized);
	exit (0);
}

void	m_flag(lem_data *d, lem_data *f)
{
	if (f->best_moves < d->best_moves)
		ft_printf(">>>> %d <<<<\n", f->best_moves);
	else
		ft_printf(">>>> %d <<<<\n", d->best_moves);
	exit (0);
}

void	s_flag(lem_data *d, lem_data *f)
{
	ft_printf("{yellow}>>>> >>>> >>>> Test results: <<<< <<<< <<<<\n");
	if (f->best_moves < d->best_moves)
		d->best_moves = f->best_moves;
	ft_printf("{green}Lem-in best result: %d", d->best_moves);
	ft_printf("{red}     %+3d", d->best_moves - f->optimized);
	ft_printf("{blue}\nRequired: %12d\n", f->optimized);
	exit (0);
}
