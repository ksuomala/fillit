/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:52:05 by jhakonie          #+#    #+#             */
/*   Updated: 2020/10/19 21:15:55 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_crdcmp(t_tet *head)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (head->x[i] == head->next->x[i] && head->y[i] == head->next->y[i])
			i++;
		else
			return (1);
	}
	return (0);
}

/*
**	This function checks whether the shapes of the tetriminos are the same.
*/

int		ft_shapecmp(t_tet *head)
{
	if (ft_lstsize(head) == 1)
		return (0);
	while (head->next->next && !ft_crdcmp(head))
		head = head->next;
	return (ft_crdcmp(head));
}

void	ft_solve_diff_shape(t_tet *head, char **test, size_t side)
{
	while (!(ft_backtracker(head, test, side)))
	{
		ft_free2d(test);
		side++;
		if (!(test = ft_create_grid(side)))
		{
			ft_lstfree(&head);
			ft_putendl("error");
			exit(0);
		}
	}
	ft_print_grid(test);
	ft_free2d(test);
}

void	ft_solve_same_shape(t_tet *head, char **test, size_t side)
{
	while (!(ft_simple_solver(head, test, side)))
	{
		ft_free2d(test);
		side++;
		if (!(test = ft_create_grid(side)))
		{
			ft_lstfree(&head);
			ft_putendl("error");
			exit(0);
		}
	}
	ft_print_grid(test);
	ft_free2d(test);
}

void	ft_resolution(t_tet *head, size_t side)
{
	char	**test;

	if (!(test = ft_create_grid(side)))
	{
		ft_putendl("error");
		return ;
	}
	if (ft_shapecmp(head))
		ft_solve_diff_shape(head, test, side);
	else
		ft_solve_same_shape(head, test, side);
}
