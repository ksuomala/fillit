/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:47:58 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/12 18:23:21 by ksuomala         ###   ########.fr       */
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

/*	ft_putstr("y = ");
	ft_putnbr(y);
	ft_n(1);
	ft_putstr("x = ");
	ft_putnbr(x);
	ft_n(1); */
	side = ft_strlen(grid[0]);
	if (head->y[0] + y >= side || head->y[1] + y >= side ||\
	head->y[2] + y >= side || head->y[3] + y >= side)
		return (0);
	if (grid[head->y[0] + y][head->x[0] + x] != '.')
	{
		//		ft_putendl("error at [0]");
		return (0);
	}
	if (grid[head->y[1] + y][head->x[1] + x] != '.')
	{
		//		ft_putendl("error at [1]");
		return (0);
	}
	if (grid[head->y[2] + y][head->x[2] + x] != '.')
	{
		//		ft_putnbr(x);
		//		ft_putchar(grid[head->y[2] + y][head->x[2] + x]);
		//		ft_putendl("error at [2]");
		return (0);
	}
	if (grid[head->y[3] + y][head->x[3] + x] != '.')
	{
//		ft_putchar(grid[head->y[3] + y][head->x[3] + x]);
		//		ft_putendl("error at [3]");
		return (0);
	}

	return (1);
}

/*
**	I want to modify check_print so it will return the pointer to the next tetrimino that is not printed
**	on the grid.
*/

t_tet	*ft_check_print(t_tet *head, char **grid, size_t side)
{
	size_t y;

//	ft_putendl("checking print");
	y = 0;
//	ft_print_grid(grid);
	while (y < side && head)
	{
//		ft_putendl("segg");
//		ft_putchar(head->print);
//		ft_putnbr(y);
		if (ft_strchr(grid[y], head->print))
		{
			head = head->next;
			y = 0;
		}
		y++;
	}
//	ft_putendl("+");
//	if (!head)
//		ft_putendl("head is null");
	return (head);
}

/*
**	I want to create a temp t_tet, and draw that on the grid. If it fails I want to draw the next one.
**	Backtracker function sets the temp variable to the first tetrimino that has not been printed on
**	the grid.
*/

int ft_backtracker(t_tet *head, char **grid)
{
	int		y;
	int		x;
	int		side;
	t_tet	*c;
	t_tet	*temp;

//	ft_putendl("backtracker");
	side = ft_strlen(grid[0]);
//	ft_putendl("222");
	temp = ft_check_print(head, grid, side);
//	ft_putendl("11111");
//	ft_putstr("head print = ");
//	ft_putchar(head->print);
//	ft_n(1);
	if (!temp)
		return (1);
	y = 0;
	x = 0;
	while (y < side)
	{
		while (x < side)
		{
//			ft_putnbr(ft_fit_tet(head, grid, y, x));
			if (ft_fit_tet(temp, grid, y, x))
			{
//				ft_putstr("fit tet ");
				ft_save_tet(temp, grid, y, x);
				//					ft_print_grid(grid);
				if (ft_backtracker(head, grid))
					return (1);
				c = temp;
//				if ((temp = ft_check_print(temp, grid, side)) == NULL)
//					return (0);
				ft_rem_char(c, grid, y, x);
//				x = -1;
//				y = -1;
			}
			x++;
		}
		x = 0;
		y++;
//		ft_putnbr(y);
	}

	return (0);
}

void ft_resolution(t_tet *head)
{
	char **test;

	test = ft_get_grid(head);
	//	ft_putstr("test = ");
	//	ft_putendl(test[0]);
	if (ft_backtracker(head, test))
	{
		ft_putendl("END");
		ft_print_grid(test);
		return;
	}
	//	free
	ft_putendl("RECURSION");
	ft_resolution(head);
}