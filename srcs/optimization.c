/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:22:37 by mybenzar          #+#    #+#             */
/*   Updated: 2019/08/01 15:31:51 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

static int		find_new_max_path(t_lemin *data, int limit)
{
	int			i;
	int			max;
	t_lstpat	*tmp;

	i = 0;
	tmp = data->exit_paths;
	max = tmp->path[0];
	while (i < limit)
	{
		if (tmp->path[0] > max)
			max = tmp->path[0];
		tmp = tmp->next;
		i++;
	}
	return (max);
}

int				ants_dispatcher(t_lemin *data, int limit)
{
	t_lstpat	*tmp;
	int			result;
	int			i;

	result = 0;
	i = 0;
	tmp = data->exit_paths;
	while (i < limit && tmp)
	{
		result += (data->path_size - tmp->path[0]);
		tmp = tmp->next;
		i++;
	}
	result = data->nbr_lem - result;
	data->surplus = result % limit;
	result /= limit;
	data->max_flow = limit;
	return (result);
}

int				find_right_path_number(t_lemin *data)
{
	int	prev_turns;
	int	limit;

	limit = data->max_flow;
	prev_turns = data->nbr_lem;
	while (ants_dispatcher(data, limit) + data->path_size <= prev_turns)
	{
		while (ants_dispatcher(data, limit) == -1)
			limit--;
		prev_turns = ants_dispatcher(data, limit) + data->path_size;
		data->path_size = find_new_max_path(data, limit);
		limit--;
	}
	return (ants_dispatcher(data, limit + 1));
}
