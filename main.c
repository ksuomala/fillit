/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:38:50 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/13 16:12:25 by ksuomala         ###   ########.fr       */
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
	if (!(new = (t_tet *)malloc(sizeof(t_tet))))
		return (NULL);
	if (!head)
		head = new;
	else
	{
		temp = head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	i = ft_lstsize(head);
	if (i > 26)
		return (NULL);
	new->print = 'A' + i - 1;
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
			return (1);
		i++;
	}
	return (0);
}

int			ft_savehsh(int y, int x, t_tet *crd, char **tet)
{
	int	i;
	int	a;

	i = crd->count;
	if (i > 3)
		return (0);
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

int		ft_isvalid(char **tet, int y, int x, t_tet *crd)
{
	if (!ft_savehsh(y, x, crd, tet))
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

int		ft_hashcount(char **arr, t_tet *head)
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

int	ft_findhsh(char *s)
{
	int i;

	i = 0;
	while(s[i] != '#' && s[i])
		i++;
	if (!s[i])
		return (-1);
	return (i);
}

t_tet	*ft_coordinates(char **tet, t_tet *head)
{
	t_tet	*last;
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	if (!(head = ft_createnode(head)))
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
				if (ft_isvalid(tet, y, x, last))
				{
					y = 4;
					break;
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

int		ft_istet(char *line, int n)
{
	int i;

	i = 0;
	if ((n != 21 && n != 20) || line[4] != '\n' || line[9] != '\n' || line[14] != '\n' || line[19] != '\n')
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

void	ft_free2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_printcoordinates(t_tet *head)
{
	int i;

	i = 0;
	while (head)
	{
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

char **ft_tet_grid(char *line)
{
	char		**tet;
	int	i;
	int			sub;

	i = 0;
	sub = 0;
	tet = (char **)malloc(sizeof(char *) * 4 + 1);
	tet[4] = NULL;
	while (i < 4)
	{
		tet[i] = ft_strsub(line, sub, 5);
		sub = sub + 5;
		i++;
	}
	return (tet);
}

/*
**	If it's a square or a straight line, shape == 1. If all shapes are sq, or all shapes are line,
**	return 1. Otherwise return 0.
*/

int	ft_shapecmp(t_tet *head)
{
	while (head->next->next && head->shape == head->next->shape)
		head = head->next;
	return (head->shape - head->next->shape);
}

int	ft_shape(t_tet *head)
{
	t_tet	*temp;

	temp = head;
	while(temp)
	{
		if (temp->x[0] == 0 && temp->x[1] == 1 && temp->x[2] == 1 && temp->x[3]\
		== 0 && temp->y[0] == 0 && temp->y[1] == 0 && temp->y[2] == 1 &&\
		temp->y[3] == 1)
			temp->shape = 1;
		else if (temp->x[0] == 0 && temp->x[1] == 0 && temp->x[2] == 0 && temp->x[3]\
		== 0 && temp->y[0] == 0 && temp->y[1] == 1 && temp->y[2] == 2 &&\
		temp->y[3] == 3)
			temp->shape = 1;
		else if (temp->x[0] == 0 && temp->x[1] == 1 && temp->x[2] == 2 && temp->x[3]\
		== 3 && temp->y[0] == 0 && temp->y[1] == 0 && temp->y[2] == 0 &&\
		temp->y[3] == 0)
			temp->shape = 1;
		else
			temp->shape = 0;
		temp = temp->next;
	}
	if (ft_shapecmp(head) || !head->shape)
		return (1);
	return (0);
}

t_tet	*ft_read(int fd, t_tet *head)
{
	int				n;
	char			line[21];
	char			**tet;

	n = read(fd, &line, 21);
	if (n < 20 || !ft_istet(line, n))
		return (NULL);
	line[19] = '\0';
	tet = ft_tet_grid(line);
	if (!(head = ft_coordinates(tet, head)))
		return (NULL);
	ft_free2d(tet);
	if (n == 21)
		return (ft_read(fd, head));
	return (head);
}

int		main(int ac, char **av)
{
	int		fd;
	t_tet	*head;

	head = NULL;
	if (ac != 2)
	{
		ft_putendl("usage: ./fillit source_file");
		exit(0);
	}
	fd = open(av[1], O_RDONLY);
	if (!(head = ft_read(fd, head)))
	{
		ft_putendl("error");
		return (0);
	}
	ft_resolution(head);
	return (0);
}
