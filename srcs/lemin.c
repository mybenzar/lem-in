/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:57:34 by mybenzar          #+#    #+#             */
/*   Updated: 2019/09/08 15:08:14 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int		translate_lstrom_to_tab(t_lemin *data)
{
	t_lstrom	*tmp;
	int			i;

	i = 0;
	tmp = data->rooms;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (i == 0 || !(data->room_tab = (t_lstrom **)malloc(sizeof(t_lstrom *) * i)))
		return (1);
	i = 0;
	tmp = data->rooms;
	while (tmp)
	{
		data->room_tab[i++] = tmp;
		tmp = tmp->next;
	}
	return (0);
}

static int		initialize_and_parse_data(t_lemin *data)
{
	data->begin_file = data->file;
	data->begin_file->str = NULL;
	data->file->next = NULL;
	parser(data);
	if (!(data->end) || !(data->start))
		return (1);
	return (0);
}

void			print_begin_file(t_lemin *data)
{
	while (data->begin_file)
	{
		if (data->begin_file->str)
			ft_putendl(data->begin_file->str);
		data->begin_file = data->begin_file->next;
	}
}

static int		launch_parsing_print_map(t_lemin *data)
{
	if (initialize_and_parse_data(data))
	{
		ft_putendl_fd("ERROR PARSING", 2);
		return (1);
	}
	if (translate_lstrom_to_tab(data))
		return (1);
	if (convert_parsing_to_usefull(data))
	{
		ft_putendl_fd("Something went wrong when parsing standard input", 2);
		return (1);
	}
	return (0);
}

int				main(void)
{
	t_lemin		data;
	void		*tmp;

	ft_memset(&data, 0, sizeof(t_lemin));
	if (!(data.file = (t_lstst*)malloc(sizeof(t_lstst))))
	{
		ft_putendl_fd("Initial malloc has failed, check your memory use", 2);
		return (1);
	}
	tmp = data.file;
	if (launch_parsing_print_map(&data) == 1)
		return (1);
	while (tmp)
	{
		data.file = ((t_lstst*)tmp)->next;
		free(((t_lstst*)tmp)->str);
		free(tmp);
		tmp = data.file;
	}
	free_data_after_parsing(&data, 0);
	free_data_after_printing(&data, 0);
	return (0);
}
