/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:28:04 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/12 19:56:42 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

size_t	ft_lstsize(t_tet *lst)
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

size_t ft_count_side(size_t nb)
{
	size_t i;

	i = 1;
	while (i * i < nb)
		i++;
	return (i);
}

char **ft_create_test_grid(size_t side)
{
	size_t 	n;
	char 	**test_grid;

	n = 0;
	if (!(test_grid = (char **)malloc(sizeof(char *) * (side + 1))))
		return (NULL);
	test_grid[side] = NULL;
	while (n < side)
	{
		if ((!(test_grid[n] = (char *)malloc(sizeof(char) * (side + 1)))))
			return (NULL);
		test_grid[n][side] = '\0';
		ft_memset(test_grid[n], '.', side);
		n++;
	}
	return (test_grid);
}

char **ft_get_grid(t_tet *head)
{
	size_t tet_count;
	static size_t side;
	static size_t i;

	i++;
	tet_count = ft_lstsize(head);
	if (i == 1)
		side = ft_count_side(tet_count * 4);
	if (i > 1)
		side++;
	return (ft_create_test_grid(side));
}

void ft_print_grid(char **test_grid)
{
	size_t i;

	i = 0;
	while (test_grid[i] != NULL)
	{
		ft_putendl(test_grid[i]);
		i++;
	}
}