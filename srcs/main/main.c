/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:27:58 by ppiirone          #+#    #+#             */
/*   Updated: 2022/08/21 15:28:01 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int	main(int argc, char **argv)
{
	lem_data	*data;
	lem_data	*flow;

	data = (lem_data *)malloc(sizeof(lem_data));
	flow = (lem_data *)malloc(sizeof(lem_data));
	if (data == NULL || flow == NULL)
		exit(0);
	input(flow);
	copy_input(flow, data);
	solve_paths(data);
	solve_flow(flow);
	//if (argc == 2 && ft_strcmp(argv[1], "-t") == 0)
	//	t_flag(data, flow);
	if (argc == 2 && ft_strcmp(argv[1], "-m") == 0)
		m_flag(data, flow);
	print_input(flow);
	if (flow->best_moves < data->best_moves)
		send_ants(flow);
	else
		send_ants(data);
	return (0); // change to exit
}
