/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isvalid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:29:01 by ksuomala          #+#    #+#             */
/*   Updated: 2020/09/08 00:46:24 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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

	i = crd->count;
	if (i > 3)
		return (0);
	if (i == 0)
		ft_define_min(y, x, crd, tet);
	crd->y[i] = y - crd->min_y;
	crd->x[i] = x - crd->min_x;
	crd->count++;
	return (1);
}

void	ft_define_min(int y, int x, t_tet *crd, char **tet)
{
	crd->min_y = y;
	if (y < 3 && x > 0 && tet[y + 1][x] == '#')
	{
		if (y < 2 && tet[y + 1][x - 1] != '#')
			y++;
		if (tet[y + 1][x - 1] == '#')
		{
			while (x > 0 && tet[y + 1][x - 1] == '#')
				x--;
		}
	}
	crd->min_x = x;
}

/*
**	ft_isvalid checks that the tetrimino has 4 '#' chars lined up, and saves
**	their coordinates with ft_savehsh.
*/

int		ft_isvalid(char **tet, int y, int x, t_tet *crd)
{
	if (!ft_savehsh(y, x, crd, tet))
		return (0);
	if (x < 3 && tet[y][x + 1] == '#')
		if (!ft_listcmp(y, x + 1, crd))
			if (!ft_isvalid(tet, y, x + 1, crd))
				return (0);
	if (x > 0 && tet[y][x - 1] == '#')
		if (!ft_listcmp(y, x - 1, crd))
			if (!ft_isvalid(tet, y, x - 1, crd))
				return (0);
	if (y < 3 && tet[y + 1][x] == '#')
		if (!ft_listcmp(y + 1, x, crd))
			if (!ft_isvalid(tet, y + 1, x, crd))
				return (0);
	return (1);
}
