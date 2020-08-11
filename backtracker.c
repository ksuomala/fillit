/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:47:58 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/11 19:14:07 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void ft_save_tet(t_tet *head, char **grid, size_t y, size_t x)
{
	grid[head->y[0] + y][head->x[0] + x] = head->print;
	grid[head->y[1] + y][head->x[1] + x] = head->print;
	grid[head->y[2] + y][head->x[2] + x] = head->print;
	grid[head->y[3] + y][head->x[3] + x] = head->print;
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
	ft_n(1);
	return (1);
}

int ft_check_print(t_tet *head, char **grid, size_t side)
{
	size_t y;

	y = 0;
	if (!head)
		return (0);
	while (y < side)
	{
		//		ft_putstr("segfault?");
		if (ft_strchr(grid[y], head->print))
			return (1);
		y++;
	}
	//	ft_putendl("NO");
	return (0);
}

int ft_backtracker(t_tet *head, char **grid)
{
	size_t y;
	size_t x;
	size_t side;
	//
	ft_putendl("backtracker");
	side = ft_strlen(grid[0]);
	ft_putnbr(999);
	ft_putnbr(side);
	while (ft_check_print(head, grid, side))
	{
		ft_putendl("next mino");
		head = head->next;
	}
	ft_putnbr(666);
	if (!head)
		return (1);
	y = 0;
	x = 0;
	while (y < side)
	{
		while (x < side)
		{
//			ft_putnbr(ft_fit_tet(head, grid, y, x));
			if (ft_fit_tet(head, grid, y, x))
			{
				ft_putstr("fit tet ");
				ft_save_tet(head, grid, y, x);
				//					ft_print_grid(grid);
				return (ft_backtracker(head, grid));
			}
			x++;
		}
		x = 0;
		y++;
		ft_putnbr(y);
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