/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:31:27 by ksuomala          #+#    #+#             */
/*   Updated: 2020/09/08 12:07:41 by jhakonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	*ft_return_null(t_tet **head)
{
	if (*head)
		ft_lstfree(head);
	return (NULL);
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

void	ft_lstfree(t_tet **ptr)
{
	t_tet	*temp;

	while (*ptr)
	{
		temp = (*ptr)->next;
		free(*ptr);
		*ptr = temp;
	}
	*ptr = NULL;
}

char	**ft_tet_grid(char *line)
{
	char	**tet;
	int		i;
	int		sub;

	i = 0;
	sub = 0;
	if (!(tet = (char **)malloc(sizeof(char *) * (4 + 1))))
		return (NULL);
	tet[4] = NULL;
	while (i < 4)
	{
		if (!(tet[i] = ft_strsub(line, sub, 4)))
		{
			ft_free2d(tet);
			return (NULL);
		}
		sub = sub + 5;
		i++;
	}
	return (tet);
}

t_tet	*ft_createnode(t_tet *head)
{
	t_tet	*temp;
	t_tet	*new;
	int		i;

	temp = head;
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
	new->next = NULL;
	i = ft_lstsize(head);
	new->print = 'A' + i - 1;
	new->count = 0;
	new->min_x = 0;
	new->min_y = 0;
	ft_memset(new->x, 0, sizeof(new->x));
	ft_memset(new->y, 0, sizeof(new->y));
	return (head);
}
