/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:38:50 by ksuomala          #+#    #+#             */
/*   Updated: 2020/09/08 14:19:36 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	ft_hashcount checks that there are no hashes around the tetriminoes.
*/

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

/*
**	ft_findhash returns the index to the first hash found in *s.
*/

int		ft_findhash(char *s)
{
	int i;

	i = 0;
	while (s[i] != '#' && i < 4)
		i++;
	if (i == 4)
		return (-1);
	return (i);
}

/*
**	ft_coordinates creates an element at the end of our list, and checks that
**	tet is a valid tetrimino with ft_findhash and ft_isvalid.
*/

t_tet	*ft_coordinates(char **tet, t_tet *head)
{
	t_tet	*last;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!(head = ft_createnode(head)))
		return (NULL);
	last = head;
	while (last->next)
		last = last->next;
	while (y < 4)
	{
		if ((x = ft_findhash(tet[y])) >= 0)
			if (ft_isvalid(tet, y, x, last))
				break ;
		y++;
	}
	if (ft_hashcount(tet, head))
		return (head);
	return (NULL);
}

/*
**	Ft_read reads our input file one tetrimino (21 or 20 characters) at a time
**	and checks that it contains right characters in right places with ft_istet.
**	It continues reading recursively, until read does not return 21.
*/

t_tet	*ft_read(int fd, t_tet *head)
{
	int				n;
	char			line[21];
	char			**tet;
	t_tet			*temp;

	temp = head;
	n = read(fd, &line, 21);
	if (n < 20 || !ft_istet(line, n))
		return (ft_return_null(&temp));
	if (!(tet = ft_tet_grid(line)))
		return (ft_return_null(&temp));
	if (!(head = ft_coordinates(tet, head)))
	{
		ft_free2d(tet);
		return (ft_return_null(&temp));
	}
	ft_free2d(tet);
	if (n == 21)
		return (ft_read(fd, head));
	if (ft_lstsize(head) > 26)
		return (ft_return_null(&temp));
	return (head);
}

int		main(int ac, char **av)
{
	int		fd;
	t_tet	*head;
	size_t	side;

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
	side = ft_count_side(4 * ft_lstsize(head));
	ft_resolution(head, side);
	ft_lstfree(&head);
	return (0);
}
