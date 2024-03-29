/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:42:58 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/20 17:50:32 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	queue_add(t_queue **last, t_queue *new)
{
	if (!last)
		return ;
	if (!*last)
		*last = new;
	else
	{
		new->prev = *last;
		(*last)->next = new;
	}
	(*last) = (*last)->next;
}
