/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bread_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 14:59:08 by mybenzar          #+#    #+#             */
/*   Updated: 2019/08/01 15:26:37 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"
#include <stdlib.h>

static void		initialize_ek(t_lemin *data, t_queue *end, int *i, int *j)
{
	data->path[1] = end->room;
	data->resid[end->room][end->parent] = 0;
	data->resid[end->parent][end->room] = 0;
	*i = 2;
	*j = end->parent;
}

/*
**	--> edmunds_karp : updates the residual map to make sure we don't cross
**	over paths we've already crossed before.
*/

static int		edmund_karps(t_lemin *data, t_queue *end)
{
	int		i;
	int		j;
	t_queue	*tmp;

	if (!(data->path = (int*)malloc(sizeof(int) * (data->nbr_room + 2))))
		return (1);
	initialize_ek(data, end, &i, &j);
	while (end)
	{
		if (end->room == j)
		{
			data->path[i++] = j;
			data->resid[end->room][j] = 0;
			data->resid[j][end->room] = 0;
			j = end->parent;
		}
		else
			data->graph[end->room][0] = 1;
		if (end->prev)
			tmp = end;
		end = end->prev;
	}
	fill_distances_info_and_close_path(data, i);
	free_queue(&tmp);
	return (0);
}

static void		initialize_loop(t_lemin *data, int *i, int *j, t_queue **start)
{
	*i = start[0]->room;
	data->graph[*i][0] = 0;
	*j = 0;
}

/*
**	--> breadth_first_search : browses each node from source to find
**	its parent until it reaches the end node. When it does, it updates
**	a residual map with an Edmunds-Karp algorithm.
*/

int				breadth_first_search(t_lemin *data, int actual)
{
	t_queue		*start[2];
	t_queue		*end;
	int			i;
	int			j;

	if (!(start[0] = queue_new(NULL, 0, data->start->id)))
		return (1);
	end = start[0];
	start[1] = start[0];
	while (start[0])
	{
		initialize_loop(data, &i, &j, &start[0]);
		while (++j <= data->nbr_room)
		{
			if (verify_link_room(data, i, j) == 1)
			{
				queue_add(&end, add_to_queue(data, i, j, &start[1]));
				if (j == actual)
					return (edmund_karps(data, end));
			}
		}
		queue_forward(&start[0]);
	}
	return (free_queue(&start[1]));
}
