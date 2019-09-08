/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:11:39 by mybenzar          #+#    #+#             */
/*   Updated: 2019/09/08 15:10:40 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

static void	add_ant_and_room_to_queue(t_lstpat *tmp, int *lem, t_queue **end
	, t_queue *queue[2])
{
	t_queue		*new;

	*lem += 1;
	new = queue_new(tmp->path, *lem, tmp->path[0] - 1);
	if (*end)
		queue_add(end, new);
	else
	{
		*end = new;
		queue[0] = new;
		queue[1] = new;
	}
}

static void	fill_queue(t_lemin *data, int result, t_queue **end
	, t_queue *queue[2])
{
	t_lstpat	*tmp;
	static int	lem = 0;
	int			i;

	tmp = data->exit_paths;
	i = 1;
	while (tmp != NULL && i <= data->max_flow)
	{
		if (lem < data->nbr_lem && i <= data->surplus)
		{
			data->surplus--;
			add_ant_and_room_to_queue(tmp, &lem, end, queue);
		}
		else if (tmp->path[0] <= result && lem < data->nbr_lem)
		{
			if (!(tmp->path[0] == result && tmp->path[0] == data->path_size))
				add_ant_and_room_to_queue(tmp, &lem, end, queue);
		}
		i++;
		tmp = tmp->next;
	}
}

static void	print_ants(t_lemin *data, int result, t_queue **end
	, t_queue *queue[2])
{
	t_queue	*wait;
	t_queue	*new;

	wait = *end;
	while (queue[0] && wait != queue[0]->prev)
	{
		if (queue[0]->room > 1)
		{
			new = queue_new(queue[0]->ptr, queue[0]->parent
				, queue[0]->room - 1);
			queue_add(end, new);
		}
		ft_putchar('L');
		ft_putnbr(queue[0]->parent);
		ft_putchar('-');
		ft_putstr(
			data->room_tab[((int*)queue[0]->ptr)[queue[0]->room] - 1]->name);
		queue_forward(&queue[0]);
		if (queue[0] && (!(result - 1) || wait != queue[0]->prev))
			ft_putchar(' ');
	}
	if (queue[0])
		ft_putchar('\n');
}

static int	check_max_flow(t_lemin *data, int *result)
{
	if (!data->max_flow)
		return (1);
	print_begin_file(data);
	if (data->max_flow < 3)
		*result = ants_dispatcher(data, data->max_flow) + data->path_size;
	else
		*result = find_right_path_number(data) + data->path_size;
	return (0);
}

int			display(t_lemin *data)
{
	int		result;
	t_queue	*queue[2];
	t_queue	*end;

	end = NULL;
	queue[0] = NULL;
	queue[1] = NULL;
	result = 0;
	if (check_max_flow(data, &result))
		return (1);
	while (result > 0)
	{
		fill_queue(data, result, &end, queue);
		print_ants(data, result, &end, queue);
		result--;
	}
	ft_putchar('\n');
	while (queue[1])
	{
		queue[0] = queue[1]->next;
		free(queue[1]);
		queue[1] = queue[0];
	}
	return (0);
}
