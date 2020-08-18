/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:31:27 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/17 15:02:19 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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

t_tet	*ft_createnode(t_tet *head)
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
