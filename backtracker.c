/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:47:58 by ksuomala          #+#    #+#             */
/*   Updated: 2020/09/08 13:57:03 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
