/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:20:17 by mybenzar          #+#    #+#             */
/*   Updated: 2019/08/02 16:46:30 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemin.h"
#include "libft.h"
#include <stdio.h>

int			free_data_after_printing(t_lemin *data, int type)
{
	void	*tmp;

//	while (data->begin_file)
//	{
//		tmp = data->begin_file->next;
//		free(data->begin_file->str);
//		free(data->begin_file);
//		data->begin_file = (t_lstst*)tmp;
//	}
	while (data->exit_paths)
	{
		tmp = data->exit_paths->next;
		free(data->exit_paths->path);
		free(data->exit_paths);
		data->exit_paths = (t_lstpat*)tmp;
	}
	while (data->file)
	{
		tmp = data->file->next;
		free(data->file->str);
		free(data->file);
		data->file = (t_lstst*)tmp;
	}
	free(data->room_tab);
	return (type);
}

static void	free_graph_and_resid(t_lemin *data)
{
	int	i;

	i = 0;
	if (data->graph && data->resid)
	{
		while (i <= data->nbr_room)
		{
			free(data->graph[i]);
			free(data->resid[i++]);
		}
		free(data->graph);
		free(data->resid);
	}
}

int			free_data_after_parsing(t_lemin *data, int type)
{
	void		*tmp;

	while (data->rooms)
	{
		tmp = data->rooms->next;
		free(data->rooms->name);
		free(data->rooms);
		data->rooms = (t_lstrom*)tmp;
	}
	while (data->links)
	{
		tmp = data->links->next;
		free(data->links->name1);
		free(data->links);
		data->links = (t_lstlin*)tmp;
	}
	free_graph_and_resid(data);
	return (type);
}

int			free_char_list(t_lstch **list, int type)
{
	t_lstch *tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	return (type);
}
