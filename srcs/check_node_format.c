/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem_to_list_while_parsing.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 19:24:48 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/24 17:59:12 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"
#include <stdlib.h>

/*
**	--> check_last_number_in_line : makes last validity checks and then
**	adds the room to the list.
*/

static int	check_last_number_in_line(t_lemin *data, char **str, char *test)
{
	if (!test || !ft_iswhitespace(*test))
		return (free_return((void**)str, -1));
	while (ft_iswhitespace(*test))
		test++;
	if (*test == '0')
	{
		++test;
		if (*test && !ft_iswhitespace(*test))
			return (free_return((void**)str, -1));
	}
	else
		ft_strtol(test, &test, 10);
	if (!test)
		return (free_return((void**)str, -1));
	while (ft_iswhitespace(*test))
		test++;
	if (*test)
		return (free_return((void**)str, -1));
	if (add_rom_to_list(data, *str))
		return (free_return((void**)str, -1));
	free(*str);
	return (0);
}

/*
**	--> add_node_if_well_formated : checks that each character of str
**	corresponds to a valid room name character.
*/

int			add_node_if_well_formated(t_lemin *data, char **str)
{
	int			i;
	char		*test;

	i = 0;
	if (data->actual_step != 1)
		return (-1);
	while (str[0][i] && !ft_iswhitespace(str[0][i]))
	{
		if (str[0][i] == '-' || str[0][i] < 32 || str[0][i] == 127)
			return (free_return((void**)str, -1));
		i++;
	}
	while (ft_iswhitespace(str[0][i]))
		i++;
	if (!str[0][i])
		return (free_return((void**)str, -1));
	if (str[0][i] == '0')
	{
		if (!ft_iswhitespace(str[0][++i]))
			return (free_return((void**)str, -1));
		test = *str + i;
	}
	else
		ft_strtol(*str + i, &test, 10);
	return (check_last_number_in_line(data, str, test));
}
