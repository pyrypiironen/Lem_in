/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:50:28 by ppiirone          #+#    #+#             */
/*   Updated: 2022/08/21 14:50:29 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

# define ARRAY_SIZE	42

typedef struct	s_room
{
	char		name[200];
	int			x;
	int			y;
	struct		s_room	*next;
	struct		s_room	**pipes;
	int			pipe_count;
				// Montako putkea huoneesta lähtee.
	int			r_index;
	int			pipe_mem;
				// Määrä muistia, joka putkia varten allokoidaan. Dynaaminen.
	int			floor;
	int			ant_nbr;
				// Monennessa kerroksessa huone on. Start on floor 0.
	int			used;
	int			*pipe_flow; /* 
							1 == empty
							2 == arrow in
							3 == arrow out
							4== arrow both ways
							*/
}				t_room;

typedef struct	lem_data
{
	struct	s_room		*head;
	struct	s_room		*current;
	struct	s_room		*start;
	struct	s_room		*end;
	struct	lem_print	*print_head;
	struct	lem_print	*print_current;
	
	int		ants;
	int		path_limit;
	char	*line;
	struct	s_room	***paths;
	int		step_array[10000];
	t_room	**hashmap;
	int		*bfs_rooms;
	int		bfs_index;
	int		*bfs_copy;
	int		room_count;
	int		path_index;
			// Reittien määrâ.
	int		path_mem;
			// Monelleko reitille on allokoitu tilaa.
	int		heat_map_index;
	int		path_depth;
			// Kuinka pitkiä reittejä etsitään
	int		**heat_map;
	int		array[10000];
	int		map_size;
	int		best_route_count;
	int		space;
	int		rec_counter;
	int		max_route_count;
	int		best_moves;
	int		*best_steps;
	struct routes	*routes_head;
	struct routes	*routes_cur;
	struct routes	*routes_best;
}			lem_data;

typedef struct routes
{	
	int				arr[10000];
	int				route_count;
	int				move_count;
	struct routes	*next;
}	routes;

typedef struct lem_print
{
	char				*str;
	struct lem_print	*next;

}				lem_print;

//		* * * * * READ_INPUT * * * * *
//		read_input.c
void	input(lem_data *d);
void	read_ants(lem_data *d);
void	read_rooms(lem_data *d);
void	read_pipes(lem_data *d);
int		skip_comments(lem_data *d);
void	create_room_array(lem_data *d);
//		read_rooms_helpers.c
int		is_room(lem_data *d, char *room);
int		is_valid(lem_data *d);
void	create_room(lem_data *d);
void	init_current(lem_data *d);
int		lem_atoi(const char *str);
//		read_pipes_helpers.c
int		is_pipe(lem_data *d);
int		create_pipe(lem_data *d, char *first, char *second);
void	add_pipe(t_room *src, t_room *dst);
void	dynamic_array(t_room *dst);
//		checking.c
void	check_duplicates(lem_data *d);
void	check_duplicate_pipes(lem_data *d);
void	check_one_step_solution(lem_data *d);
int		check_start_end(lem_data *d);

//		* * * * * FIND_PATHS * * * * *
//		pathfinder.c
void	solve_paths(lem_data *d);
void	save_path(lem_data *d, t_room **route);
void	dynamic_path_mem(lem_data *d);
void	get_floors(lem_data *d);
int		get_floors_helper(lem_data *d, int level);
//		unique.c
void	get_unique(lem_data *d);
void	find_more_routes(lem_data *d);
void	recursive_finder(lem_data *d, t_room **route, t_room *room, int steps);
//		solution_found.c
int		solution_found(lem_data *d);
void	fill_heat_map(lem_data *d);
void	dynamic_heat_map(lem_data *d);
void	copy_heat_map(lem_data *d, int **tmp);
int		is_conflict(lem_data *d, int i);
//		helpers.c
void	init_data(lem_data *d);
void	init_routes(lem_data *d);
void	init_heat_map(lem_data *d);
void	init_unique(lem_data *d);

//		* * * * * ALGORITHM
//		compare_solutions.c
void	find_best(lem_data *d);
void	get_move_counts(lem_data *d);
//		heat_map.c
int		check_heat_map(lem_data *d, int nb, int in);
int		fill_route_array(lem_data *d);
int		compare_array(lem_data *d, int nb, int in);
//		send_ants.c
void	send_ants(lem_data *d);
void	move_ants(lem_data *d, t_room ***best_paths);
void	move_ant(lem_data *d, t_room ***best_paths, int i, int j);

//		* * * * * PRINTING * * * * *
//		printing.c
void	print_error(void);
void	lem_to_print(lem_data *d);
void	print_super_solution(lem_data *d);
void	print_input(lem_data *d);

//		* * * FLOW * * *
void	flow_routes(lem_data *d);
void	bfs(lem_data *d);
void	arrows(lem_data *d, t_room *from, t_room *to, int flow);
void	add_to_empty(lem_data *d, t_room *from, t_room *to, int flow);


#endif
