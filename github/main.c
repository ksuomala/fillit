/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:38:50 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/18 18:26:42 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
