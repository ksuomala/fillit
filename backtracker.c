/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:47:58 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/13 16:08:21 by ksuomala         ###   ########.fr       */
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


int ft_fit_tet(t_tet *head, char **grid, size_t y, size_t x)
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
**	I want to modify check_print so it will return the pointer to the next tetrimino that is not printed
**	on the grid.
*/

t_tet	*ft_check_print(t_tet *head, char **grid, size_t side)
{
	size_t y;

	y = 0;
	while (y < side && head)
	{
		if (ft_strchr(grid[y], head->print))
		{
			head = head->next;
			y = 0;
		}
		y++;
	}
	return (head);
}

/*
**	I want to create a temp t_tet, and draw that on the grid. If it fails I want to draw the next one.
**	Backtracker function sets the temp variable to the first tetrimino that has not been printed on
**	the grid.
*/

int ft_simple_solver(t_tet *head, char **grid)
{
	int		y;
	int		x;
	int		side;
	t_tet	*temp;

	side = ft_strlen(grid[0]);
	temp = ft_check_print(head, grid, side);
	if (!temp)
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
				if (ft_simple_solver(head, grid))
					return (1);
				else
					return (0);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int ft_backtracker(t_tet *head, char **grid)
{
	int		y;
	int		x;
	int		side;
	t_tet	*c;
	t_tet	*temp;

	side = ft_strlen(grid[0]);
	temp = ft_check_print(head, grid, side);
	if (!temp)
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
				if (ft_backtracker(head, grid))
					return (1);
				c = temp;
				ft_rem_char(c, grid, y, x);
			}
			x++;
		}
		x = 0;
		y++;
	}

	return (0);
}

void	ft_lstfree(t_tet **ptr)
{
	t_tet	*temp;

	while(*ptr)
	{
		temp = (*ptr)->next;
		free(*ptr);
		*ptr = temp;
	}
	*ptr = NULL;
}

void ft_resolution(t_tet *head)
{
	char **test;

	test = ft_get_grid(head);

	if(ft_shape(head))
	{
		if (ft_backtracker(head, test))
		{
			ft_print_grid(test);
			ft_free2d(test);
			return ;
		}
	}
	else
	{
		if(ft_simple_solver(head, test))
		{
			ft_print_grid(test);
			ft_free2d(test);
			return ;
		}
	}
//	ft_free2d(test);
	ft_resolution(head);
}