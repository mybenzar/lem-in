/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:42:16 by mybenzar          #+#    #+#             */
/*   Updated: 2019/04/02 13:43:30 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new_str;

	if (!(new_str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(new_str, size + 1);
	return (new_str);
}
