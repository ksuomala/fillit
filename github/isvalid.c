/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isvalid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:29:01 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/18 18:32:39 by ksuomala         ###   ########.fr       */
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
**	ft_istet checks that the line contains valid tetrimino characters in their
**	right places.
*/

int		ft_istet(char *line, int n)
{
	int i;

	i = 0;
	if ((n != 21 && n != 20) || line[4] != '\n' || line[9] != '\n' || line[14]\
	!= '\n' || line[19] != '\n')
		return (0);
	if (n == 21 && line[20] != '\n')
		return (0);
	while (i < n)
	{
		if (line[i] != '#' && line[i] != '.' && line[i] != '\n')
			return (0);
		if (line[i] == '\n')
			if (i != 4 && i != 9 && i != 14 && i != 19 && i != 20)
				return (0);
		i++;
	}
	return (1);
}

/*
**	ft_listcmp is called from ft_isvalid and it checks if the coordinate is
**	already saved in the struct.
*/

int		ft_listcmp(int y, int x, t_tet *crd)
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

int		ft_savehsh(int y, int x, t_tet *crd, char **tet)
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

/*
**	ft_isvalid checks that the tetrimino has 4 '#' chars lined up, and saves
**	their coordinates with ft_savehsh.
*/

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
