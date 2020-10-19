/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:28:04 by ksuomala          #+#    #+#             */
/*   Updated: 2020/09/08 14:21:27 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

size_t		ft_lstsize(t_tet *lst)
{
	size_t i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

size_t		ft_count_side(size_t nb)
{
	size_t i;

	i = 1;
	while (i * i < nb)
		i++;
	return (i);
}

/*
**	This function creates a 2-dimensional grid made of '.' chars side x side.
*/

char		**ft_create_grid(size_t side)
{
	size_t	n;
	char	**test_grid;

	n = 0;
	if (!(test_grid = (char **)malloc(sizeof(char *) * (side + 1))))
		return (NULL);
	test_grid[side] = NULL;
	while (n < side)
	{
		if ((!(test_grid[n] = (char *)malloc(sizeof(char) * (side + 1)))))
		{
			ft_free2d(test_grid);
			return (NULL);
		}
		test_grid[n][side] = '\0';
		ft_memset(test_grid[n], '.', side);
		n++;
	}
	return (test_grid);
}

void		ft_print_grid(char **test_grid)
{
	size_t	i;

	i = 0;
	while (test_grid[i] != NULL)
	{
		ft_putendl(test_grid[i]);
		i++;
	}
}
