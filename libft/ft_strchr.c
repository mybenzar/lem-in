/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:41:25 by mybenzar          #+#    #+#             */
/*   Updated: 2019/04/02 12:07:43 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	occur;

	str = (unsigned char*)s;
	occur = (unsigned char)c;
	while (*str)
	{
		if (*str == occur)
			return ((char*)str);
		str++;
	}
	return ((c == 0 ? (char*)str : NULL));
}
