/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:24:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/17 18:19:21 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_save_tet(t_tet *head, char **grid, size_t y, size_t x)
{
	grid[head->y[0] + y][head->x[0] + x] = head->print;
	grid[head->y[1] + y][head->x[1] + x] = head->print;
	grid[head->y[2] + y][head->x[2] + x] = head->print;
	grid[head->y[3] + y][head->x[3] + x] = head->print;
}

void	ft_rem_char(t_tet *head, char **grid, size_t y, size_t x)
{
	grid[head->y[0] + y][head->x[0] + x] = '.';
	grid[head->y[1] + y][head->x[1] + x] = '.';
	grid[head->y[2] + y][head->x[2] + x] = '.';
	grid[head->y[3] + y][head->x[3] + x] = '.';
}

int		ft_fit_tet(t_tet *head, char **grid, size_t y, size_t x)
{
	size_t side;

	side = ft_strlen(grid[0]);
	if (head->y[0] + y >= side || head->y[1] + y >= side ||\
	head->y[2] + y >= side || head->y[3] + y >= side)
		return (0);
	if (grid[head->y[0] + y][head->x[0] + x] != '.')
		return (0);
	if (grid[head->y[1] + y][head->x[1] + x] != '.')
		return (0);
	if (grid[head->y[2] + y][head->x[2] + x] != '.')
		return (0);
	if (grid[head->y[3] + y][head->x[3] + x] != '.')
		return (0);
	return (1);
}

/*
**	I want to modify check_print so it will return the pointer
**	to the next tetrimino that is not printed
**	on the grid.
*/

t_tet	*ft_check_print(t_tet *head, char **grid, int side)
{
	int y;

	y = 0;
	while (y < side && head)
	{
		if (ft_strchr(grid[y], head->print))
		{
			head = head->next;
			y = -1;
		}
		y++;
	}
	return (head);
}
