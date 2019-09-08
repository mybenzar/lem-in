/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_optimizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:12:25 by mybenzar          #+#    #+#             */
/*   Updated: 2019/09/08 11:59:49 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemin.h"
#include "libft.h"
#include <stdio.h>

double		room_link_ratio(t_lemin *data)
{
	int i;
	int j;
	int	max;
	int	avg;

	i = 1;
	avg = 0;
	while (i <= data->nbr_room)
	{
		j = 1;
		max = 0;
		while (j <= data->nbr_room)
		{
			if (data->graph[i][j] == 1)
				max++;
			j++;
		}
		avg += max;
		i++;
	}
	if (avg == 0)
		return (-1);
	return ((double)data->nbr_room * 2. / (double)avg);
}

int			save_path(t_lemin *data, t_lstpat **start)
{
	t_lstpat	*tmp;

	if (!(tmp = (t_lstpat *)malloc(sizeof(t_lstpat))))
		return (1);
	tmp->path = data->path;
	if (data->exit_paths)
	{
		tmp->prev = data->exit_paths;
		data->exit_paths->next = tmp;
	}
	else
		tmp->prev = NULL;
	tmp->next = NULL;
	if (!(*start))
		*start = tmp;
	data->exit_paths = tmp;
	return (0);
}

int			flow_optimizer(t_lemin *data, int actual)
{
	int			i;
	int			j;
	int			ret;
	t_lstpat	*start;

	start = NULL;
	while (!(ret = breadth_first_search(data, actual)))
		if (save_path(data, &start) == 1)
			return (1);
	i = 1;
	while (i <= data->nbr_room)
	{
		j = 1;
		while (j <= data->nbr_room)
			data->resid[i][j++] = 1;
		data->graph[i][0] = 1;
		i++;
	}
	data->exit_paths = start;
	if (display(data))
		return (1);
	return (0);
}
