/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:58:54 by ksuomala          #+#    #+#             */
/*   Updated: 2020/06/30 19:38:16 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void			*ptr;
	unsigned char	*i;

	ptr = malloc(sizeof(void) * size);
	if (!ptr)
		return (NULL);
	i = (unsigned char *)ptr;
	ft_bzero(ptr, size);
	return (ptr);
}
