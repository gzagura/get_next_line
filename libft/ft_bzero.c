/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzagura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 18:41:57 by gzagura           #+#    #+#             */
/*   Updated: 2017/11/29 18:42:09 by gzagura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_bzero(void *ptr, size_t len)
{
	unsigned char *s;

	s = ptr;
	while (len > 0)
	{
		*s = '\0';
		s++;
		len--;
	}
}
