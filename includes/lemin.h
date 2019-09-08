/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 10:50:29 by mybenzar          #+#    #+#             */
/*   Updated: 2019/08/02 16:43:51 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

/*
** INCLUDES
*/

#include "libft.h"

/*
** DEFINES
*/

# define RED 1
# define BLACK 2
# define TRUE 1
# define FALSE 0
# define ERROR -1

/*
** TYPEDEFS
*/

typedef struct s_lemin	t_lemin;
typedef struct s_vec2	t_vec2;
typedef struct s_lstch	t_lstch;
typedef struct s_lstst	t_lstst;
typedef struct s_lstrom	t_lstrom;
typedef struct s_lstlin	t_lstlin;
typedef struct s_lstpat	t_lstpat;
typedef struct s_lstgrp	t_lstgrp;

/*
** STRUCTURES
*/

struct					s_lstpat
{
	int					*path;
	t_lstpat			*next;
	t_lstpat			*prev;
};

struct					s_lstgrp
{
	int					*path;
	t_lstgrp			*next;
};

struct					s_lstrom
{
	char				*name;
	int					id;
	t_lstrom			*next;
};

struct					s_lstst
{
	char				*str;
	int					len;
	int					line;
	t_lstst				*next;
};

struct					s_lstch
{
	char				c;
	t_lstch				*next;
};

struct					s_vec2
{
	int					x;
	int					y;
};

struct					s_lstlin
{
	char				*name1;
	int					id1;
	char				*name2;
	int					id2;
	t_lstlin			*next;
};

struct					s_lemin
{
	int					nbr_lem;
	int					nbr_room;
	int					actual_step;
	int					start_end;
	int					max_flow;
	t_lstrom			*start;
	t_lstrom			*end;
	t_lstrom			*rooms;
	t_lstrom			**room_tab;
	t_lstlin			*links;
	t_lstst				*file;
	t_lstst				*begin_file;
	t_lstpat			*exit_paths;
	int					*path;
	int					path_size;
	int					surplus;
	char				**graph;
	char				**resid;
};

/*
** PARSER
*/

int						parser(t_lemin *data);
int						check_if_line_can_probably_be_well_formated(
	t_lstch *begin, t_lemin *data, int len);
int						find_type_of_line(t_lstch *begin, t_lemin *data
	, int len);
int						add_node_if_well_formated(t_lemin *data, char **str);
int						add_link_if_well_formated(t_lemin *data, char **str);
int						add_rom_to_list(t_lemin *data, char *str);
int						find_name_in_list(t_lemin *data, char *str, int *id);
int						translate_list_to_string(t_lstch *list, char **str
	, int len);
int						convert_parsing_to_usefull(t_lemin *data);

/*
** GRAPH
*/

int						breadth_first_search(t_lemin *data, int actual);
t_queue					*add_to_queue(t_lemin *data, int i, int j, t_queue **start);
void					fill_distances_info_and_close_path(t_lemin *data, int i);
int						verify_link_room(t_lemin *data, int i, int j);
int						save_path(t_lemin *data, t_lstpat **start);
int						flow_optimizer(t_lemin *data, int actual);
int						find_right_path_number(t_lemin *data);
int						ants_dispatcher(t_lemin *data, int limit);
int						display(t_lemin *data);
void					print_begin_file(t_lemin *data);

/*
** FREE MEMORY
*/

int						free_char_list(t_lstch **list, int type);
int						free_data_after_parsing(t_lemin *data, int type);
int						free_data_after_printing(t_lemin *data, int type);
int						free_return(void **ptr, int type);
int						free_queue(t_queue **start);

#endif
