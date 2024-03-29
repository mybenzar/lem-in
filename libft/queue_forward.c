/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_forward.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:42:53 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/21 15:02:41 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		queue_forward(t_queue **begin)
{
	if (!begin)
		return ;
	if (!*begin)
		return ;
	*begin = (*begin)->next;
}
