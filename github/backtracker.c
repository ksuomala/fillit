/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:47:58 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/18 18:41:21 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_crdcmp(t_tet *head)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (head->x[i] == head->next->x[i] && head->y[i] == head->next->y[i])
			i++;
		else
			return (1);
	}
	return (0);
}

/*
**	This function checks whether the shapes of the tetriminos are the same.
*/

int		ft_shapecmp(t_tet *head)
{
	if (ft_lstsize(head) == 1)
		return (0);
	while (head->next->next && !ft_crdcmp(head))
		head = head->next;
	return (ft_crdcmp(head));
}

/*
**	The simple_solver algorithm is used if all the tetriminos are the same
**	shape.
*/

int		ft_simple_solver(t_tet *head, char **grid, int side)
{
	int		y;
	int		x;
	t_tet	*temp;

	if ((temp = ft_check_print(head, grid, side)) == NULL)
		return (1);
	y = 0;
	x = 0;
	while (y < side)
	{
		while (x < side)
		{
			if (ft_fit_tet(temp, grid, y, x))
			{
				ft_save_tet(temp, grid, y, x);
				return (ft_simple_solver(head, grid, side));
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int		ft_backtracker(t_tet *head, char **grid, int side)
{
	int		y;
	int		x;
	t_tet	*temp;

	if ((temp = ft_check_print(head, grid, side)) == NULL)
		return (1);
	y = 0;
	x = 0;
	while (y < side)
	{
		while (x < side)
		{
			if (ft_fit_tet(temp, grid, y, x))
			{
				ft_save_tet(temp, grid, y, x);
				if (ft_backtracker(head, grid, side))
					return (1);
				ft_rem_char(temp, grid, y, x);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

void	ft_resolution(t_tet *head)
{
	char	**test;
	int		side;

	test = ft_get_grid(head);
	side = ft_strlen(test[0]);
	if (ft_shapecmp(head))
	{
		if (ft_backtracker(head, test, side))
		{
			ft_print_grid(test);
			ft_free2d(test);
			return ;
		}
	}
	else
	{
		if (ft_simple_solver(head, test, side))
		{
			ft_print_grid(test);
			ft_free2d(test);
			return ;
		}
	}
	ft_free2d(test);
	ft_resolution(head);
}
