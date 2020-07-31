#ifndef		FILLIT_H
# define	FILLIT_H

# include	"libft.h"
# include	<fcntl.h>

typedef struct		s_tet
{
	char			print;
	int				count;
	int				x[4];
	int				y[4];
	struct s_tet	*next;
}					t_tet;



#endif
