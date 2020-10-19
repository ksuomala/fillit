/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakonie <jhakonie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:50:03 by ksuomala          #+#    #+#             */
/*   Updated: 2020/09/15 14:37:44 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# include <fcntl.h>

typedef	struct		s_tet
{
	char			print;
	int				min_x;
	int				min_y;
	int				count;
	int				x[4];
	int				y[4];
	struct s_tet	*next;
}					t_tet;

size_t				ft_lstsize(t_tet *lst);
size_t				ft_count_side(size_t nb);
char				**ft_create_grid(size_t side);
void				ft_print_grid(char **test_grid);
void				ft_resolution(t_tet *head, size_t side);
void				ft_free2d(char **arr);
int					ft_shape(t_tet *head);
int					ft_isvalid(char **tet, int y, int x, t_tet *crd);
char				**ft_tet_grid(char *line);
t_tet				*ft_createnode(t_tet *head);
char				**ft_tet_grid(char *line);
void				ft_lstfree(t_tet **ptr);
void				ft_free2d(char **arr);
t_tet				*ft_check_print(t_tet *head, char **grid, int side);
int					ft_fit_tet(t_tet *head, char **grid, size_t y, size_t x);
void				ft_rem_char(t_tet *head, char **grid, size_t y, size_t x);
void				ft_save_tet(t_tet *head, char **grid, size_t y, size_t x);
int					ft_istet(char *line, int n);
int					ft_hashcount(char **arr, t_tet *head);
void				ft_define_min(int y, int x, t_tet *crd, char **tet);
int					ft_backtracker(t_tet *head, char **grid, int side);
int					ft_simple_solver(t_tet *head, char **grid, int side);
void				ft_solve_same_shape(t_tet *head, char **test, size_t side);
void				ft_solve_diff_shape(t_tet *head, char **test, size_t side);
void				*ft_return_null(t_tet **head);

#endif
