/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:50:03 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/11 16:18:51 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include <fcntl.h>

typedef struct		s_tet
{
	char			print;
	int				min_x;
	int				min_y;
	int				count;
	int				x[4];
	int				y[4];
	struct s_tet	*next;
}					t_tet;

size_t	ft_lstsize(t_tet *lst);
size_t ft_count_side(size_t nb);
char **ft_create_test_grid(size_t side);
char **ft_get_grid(t_tet *head);
void ft_print_grid(char **test_grid);
void ft_resolution(t_tet *head);


#endif
