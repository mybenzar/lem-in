/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_usefull.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 20:29:59 by mybenzar          #+#    #+#             */
/*   Updated: 2019/09/08 14:17:25 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void		rework_graph(t_lemin *data)
{
	int		i;
	int		j;
	int		max;

	i = 1;
	while (i <= data->nbr_room)
	{
		j = 1;
		max = 0;
		while (j <= data->nbr_room)
		{
			if (data->graph[i][j])
				max++;
			if (max > 1)
				break ;
			j++;
		}
		if (max <= 1 && i != data->start->id && i != data->end->id)
			data->graph[i][0] = 0;
		i++;
	}
}

int			allocate_and_init_graphs(t_lemin *data)
{
	int		i;

	i = 0;
	if (!(data->graph = (char**)malloc(sizeof(char*) * (data->nbr_room + 1))))
		return (1);
	if (!(data->resid = (char**)malloc(sizeof(char*) * (data->nbr_room + 1))))
		return (1);
	while (i <= data->nbr_room)
	{
		if (!(data->graph[i] = (char*)malloc(sizeof(char)
					* (data->nbr_room + 1))))
			return (1);
		if (!(data->resid[i] = (char*)malloc(sizeof(char)
					* (data->nbr_room + 1))))
			return (1);
		ft_memset(data->graph[i], 0, data->nbr_room + 1);
		ft_memset(data->resid[i], 1, data->nbr_room + 1);
		data->graph[i++][0] = 1;
	}
	return (0);
}

int			convert_parsing_to_usefull(t_lemin *data)
{
	t_lstlin	*tmp;

	if (allocate_and_init_graphs(data))
		return (1);
	tmp = data->links;
	while (tmp)
	{
		data->graph[tmp->id1][tmp->id2] = 1;
		data->graph[tmp->id2][tmp->id1] = 1;
		if ((tmp->id1 == data->start->id || tmp->id2 == data->start->id)
			&& (tmp->id1 == data->end->id || tmp->id2 == data->end->id))
			return (42);
		tmp = tmp->next;
	}
	data->graph[data->start->id][0] = 0;
	rework_graph(data);
	return (flow_optimizer(data, data->end->id));
}
