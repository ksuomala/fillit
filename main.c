/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:38:50 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/12 17:08:11 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	I'm thinking I should check the lines for forbidden characters here and
**	make each tetrimino into a 2d array. I should first check if they are valid
**	and then create a list with all the quordinates and return that.
**
**
**	Next step would be to create functions to move my figures on the grid.
**	We should have one grid where we draw each tetrimino and start moving them.
**
**		On the last read read should also return 20. Our program will return
**		error because it
**		checks that read returns 21. Check that [20] is a newline and that there is no extra nl at end of file.f
**
**
**		Create smallest possible grid (sqrt(n of tet * 4). We need listlen.
**		Place A to the most upper left position.
** 		Move B to the right side of A. If it doesn't fit, increment y. We need move right and move down functions.
**		while (x != .) >> x++; , if ((x[i] + x) == .)
*/



t_tet		*ft_createnode(t_tet *head)
{
	t_tet	*temp;
	t_tet	*new;
	int		i;

	i = 0;
	if (!(new = (t_tet*)malloc(sizeof(t_tet))))
		return (NULL);
	if (!head)
		head = new;
	else
	{
		i++;
		temp = head;
		while (temp->next)
		{
			temp = temp->next;
			i++;
//			ft_putchar('+');
		}
		temp->next = new;
	}
	if (i > 25)
	{
		ft_putendl("too many tet");
		return (NULL);
	}
	new->print = 'A' + i;
	new->count = 0;
	new->next = NULL;
	return (head);
}

int			ft_listcmp(int y, int x, t_tet *crd)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (crd->x[i] == (x - crd->min_x) && crd->y[i] == (y - crd->min_y))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int			ft_savehsh(int y, int x, t_tet *crd, char **tet)
{
	int i;
	int a;

//	ft_putendl("saving hash");
	i = crd->count;
	if (i > 3)
	{
/*		ft_putnbr(crd->min_y);
		ft_putnbr(crd->min_x);
		ft_putstr("  ");
		ft_putnbr(y - crd->min_y);
		ft_putnbr(x - crd->min_x); */
		return (0);
	}
//	ft_putendl("here");
	a = x;
	if (i == 0)
	{
		crd->min_y = y;
		while (y < 3 && tet[y + 1][a - 1] == '#')
			a--;
		crd->min_x = a;
	}
	crd->y[i] = y - crd->min_y;
	crd->x[i] = x - crd->min_x;
	crd->count++;
	return (1);
}

int			ft_isvalid(char **tet, int y, int x, t_tet *crd)
{
	if (!ft_savehsh(y, x, crd, tet))
	{
//		ft_putendl("error savehash");
		return (0);
	}
	if (x < 4 && tet[y][x + 1] == '#')
		if (!ft_listcmp(y, x + 1, crd))
			if (!ft_isvalid(tet, y, x + 1, crd))
			{
//				ft_putendl("error x + 1");
				return (0);
			}
	if (x > 0 && tet[y][x - 1] == '#')
		if (!ft_listcmp(y, x - 1, crd))
			if (!ft_isvalid(tet, y, x - 1, crd))
			{
//				ft_putendl("error x - 1");
				return (0);
			}
	if (y > 3 && tet[y - 1][x] == '#')
		if (!ft_listcmp(y - 1, x, crd))
			if (!ft_isvalid(tet, y - 1, x, crd))
			{
//				ft_putendl("error y - 1");
				return (0);
			}
	if (y < 3 && tet[y + 1][x] == '#')
		if (!ft_listcmp(y + 1, x, crd))
			if (!ft_isvalid(tet, y + 1, x, crd))
			{
//				ft_putendl("error y + 1");
				return (0);
			}
//	ft_putendl("return isvalid");
	return (1);
}

int			ft_hashcount(char **arr, t_tet *head)
{
	int x;
	int y;
	int count;

//	ft_putendl("hshcount");
	while (head->next)
		head = head->next;
	if (head->count != 4)
		return (0);
	x = 0;
	y = 0;
	count = 0;
	while (y < 4)
	{
		while (x < 4)
		{
			if (arr[y][x] == '#')
				count++;
			x++;
		}
		x = 0;
		y++;
	}
	if (count != 4)
		return (0);
	return (1);
}

t_tet		*ft_coordinates(char **tet, t_tet *head)
{
	t_tet		*last;
	size_t		x;
	size_t		y;

	x = 0;
	y = 0;
	if(!(head = ft_createnode(head)))
		return (NULL);
	last = head;
	while (last->next)
		last = last->next;
	while (y < 4)
	{
		while (x < 4)
		{
			if (tet[y][x] == '#')
			{
//				ft_putendl("found hash");
				if (ft_isvalid(tet, y, x, last))
				{
					y = 4;
					break ;
				}
			}
			x++;
		}
		x = 0;
		y++;
	}
	if (ft_hashcount(tet, head))
		return (head);
	return (NULL);
}

int			ft_istet(char *line, int n)
{
	int i;

	i = 0;
	if ((n != 21 && n != 20) || line[4] != '\n' || line[9] != '\n'\
	|| line[14] != '\n' || line[19] != '\n')
		return (0);
	if (n == 21 && line[20] != '\n')
		return (0);
	while (i < n)
	{
		if (line[i] != '#' && line[i] != '.' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void		ft_free2d(char **arr)
{
	int i;

	i = 0;
	while (i < 4)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
//	ft_putendl("FREED");
}

void ft_printcoordinates(t_tet *head)
{
	int i;

	i = 0;
	ft_putstr("y[3] = ");
	ft_putnbr(head->y[3]);
	ft_n(1);
	while (head)
	{
//		ft_putendl("head loop");
		while (i < 4)
		{
			ft_putnbr(head->y[i]);
			ft_putnbr(head->x[i]);
			i++;
		}
		i = 0;
		head = head->next;
	}
}


t_tet		*ft_read(int fd)
{
	int				i;
	int				n;
	int				sub;
	char			line[21];
	char			**grid;
	static t_tet	*head;

	grid = (char**)malloc(sizeof(char*) * 4);
	i = 0;
	n = read(fd, &line, 21);
	if (n < 20 || !ft_istet(line, n))
	{
		ft_putstr("n20 or !ftistet\n");
		return (NULL);
	}
	line[19] = '\0';
	sub = 0;
	while (i < 4)
	{
		grid[i] = ft_strsub(line, sub, 5);
		sub = sub + 5;
		i++;
	}
	ft_putendl("before coordinates");
	if (!(head = ft_coordinates(grid, head)))
	{
//		ft_putendl("coordinates");
		return (NULL);
	}
	ft_free2d(grid);
	if (n == 21)
	{
//		ft_putendl("n = 21");
		return (ft_read(fd));
	}
	return (head);
}


int			main(int ac, char **av)
{
	int		i;
	int		fd;
	t_tet	*mino;

	if (ac != 2)
	{
		ft_putendl("error1");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (!(mino = ft_read(fd)))
	{
		ft_putendl("error2");
		return (0);
	}
//	ft_printcoordinates(mino);

//	test = ft_get_grid(mino);
//	ft_print_grid(test);
//	ft_putstr("A3 = ");
//	ft_putnbr(ft_lstsize(mino));
	ft_n(1);
	ft_resolution(mino);
	i = 0;
	return (0);
}
