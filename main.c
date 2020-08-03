/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:38:50 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/03 18:05:30 by ksuomala         ###   ########.fr       */
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
**	....	This input gives segfault with 3 tetriminos. On the last read read
**	.#..	should also return 20. Our program will return error because it
**	####	checks that read returns 21.
**	....
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
		}
		temp->next = new;
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
		if (crd->x[i] == x && crd->y[i] == y)
		{
			ft_putendl("already saved");
			return (1);
		}
		i++;
	}
	return (0);
}

int			ft_savehsh(int y, int x, t_tet *crd)
{
	int i;

	i = crd->count;
	if (i > 3)
		return (0);
	crd->y[i] = y;
	crd->x[i] = x;
	crd->count++;
	return (1);
}

int			ft_isvalid(char **tet, int y, int x, t_tet *crd)
{
	if (!ft_savehsh(y, x, crd))
		return (0);
	if (x < 4 && tet[y][x + 1] == '#')
		if (!ft_listcmp(y, x + 1, crd))
			if (!ft_isvalid(tet, y, x + 1, crd))
				return (0);
	if (x > 0 && tet[y][x - 1] == '#')
		if (!ft_listcmp(y, x - 1, crd))
			if (!ft_isvalid(tet, y, x - 1, crd))
				return (0);
	if (y > 3 && tet[y - 1][x] == '#')
		if (!ft_listcmp(y - 1, x, crd))
			if (!ft_isvalid(tet, y - 1, x, crd))
				return (0);
	if (y < 3 && tet[y + 1][x] == '#')
		if (!ft_listcmp(y + 1, x, crd))
			if (!ft_isvalid(tet, y + 1, x, crd))
				return (0);
	return (1);
}

int			ft_hashcount(char **arr, t_tet *head)
{
	int x;
	int y;
	int count;

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
	head = ft_createnode(head);
	last = head;
	while (last->next)
		last = last->next;
	while (y < 4)
	{
		while (x < 4)
		{
			if (tet[y][x] == '#')
				if (ft_isvalid(tet, y, x, last))
					break ;
			x++;
		}
		x = 0;
		y++;
	}
	if (ft_hashcount(tet, head))
		return (head);
	return (NULL);
}

int			ft_istet(char *s)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (s[i] != '#' && s[i] != '.')
		{
			ft_putendl("wrong char");
			return (0);
		}
		i++;
	}
	if (s[i] != '\n')
		return (0);
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
	ft_putendl("FREED");
}

t_tet		*ft_read(int fd)
{
	int				i;
	int				n;
	char			line[21];
	char			**grid;
	static t_tet	*head;

	grid = (char**)malloc(sizeof(char*) * 4);
	i = 0;
	if (!(n = read(fd, &line, 21)))
		return (head);
	if ((n != 21 && n != 20) || line[4] != '\n' || line[9] != '\n'\
	|| line[14] != '\n' || line[19] != '\n')
		return (NULL);
	line[19] = '\0';
	n = 0;
	while (i < 4)
	{
		grid[i] = ft_strsub(line, n, 5);
		n = n + 5;
		i++;
	}
	if (!(head = ft_coordinates(grid, head)))
		return (NULL);
	ft_free2d(grid);
	return (ft_read(fd));
}

int			main(int ac, char **av)
{
	int		i;
	int		fd;
	t_tet	*mino;

	if (ac != 2)
	{
		ft_putendl("error");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (!(mino = ft_read(fd)))
	{
		ft_putendl("error");
		return (0);
	}
	ft_putchar(mino->print);
	ft_putchar(mino->next->print);
	ft_putchar(mino->next->next->print);
	ft_putchar(mino->next->next->next->print);
	ft_putnbr(mino->y[1]);
	ft_putnbr(mino->next->y[1]);
	ft_putnbr(mino->next->next->y[1]);
	ft_putnbr(mino->next->next->next->y[1]);
	i = 0;
	return (0);
}
