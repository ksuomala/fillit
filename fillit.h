/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:50:03 by ksuomala          #+#    #+#             */
/*   Updated: 2020/08/03 16:50:45 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include <fcntl.h>

typedef struct		s_tet
{
	char			print;
	int				count;
	int				x[4];
	int				y[4];
	struct s_tet	*next;
}					t_tet;

#endif
