/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 15:12:19 by mybenzar          #+#    #+#             */
/*   Updated: 2019/08/01 15:48:09 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"
#include <stdlib.h>

int		verify_link_room(t_lemin *data, int i, int j)
{
	if (data->graph[i][j] == 1 && data->graph[j][0] == 1
		&& data->resid[i][j] == 1 && data->resid[j][i] == 1)
		return (1);
	return (0);
}

void	fill_distances_info_and_close_path(t_lemin *data, int i)
{
	data->path[i] = 0;
	data->path[0] = i - 1;
	data->max_flow++;
	if (i - 1 > data->path_size)
		data->path_size = i - 1;
}

t_queue	*add_to_queue(t_lemin *data, int i, int j, t_queue **start)
{
	t_queue		*tmp;

	data->graph[j][0] = 0;
	if (!(tmp = queue_new(NULL, i, j)))
	{
		free_queue(&start[1]);
		return (NULL);
	}
	return (tmp);
}

int		free_queue(t_queue **start)
{
	t_queue *tmp;

	if (*start)
	{
		while ((*start)->prev)
			*start = (*start)->prev;
		while ((*start))
		{
			tmp = (*start)->next;
			free(*start);
			*start = tmp;
		}
	}
	return (2);
}
