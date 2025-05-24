#ifndef CONWAY_H
# define CONWAY_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <X11/X.h>
# include "get_next_line.h"
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_map
{
	size_t	width;
	size_t	height;
	bool	**cell;
}	t_map;

typedef struct s_wrap
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_data	data;
	t_map	map;
}	t_wrap;

typedef enum e_keycode
{
	KEYCODE_Q = 113,
	KEYCODE_ESC = 65307
}	t_keycode;

bool	read_from_file(t_map *map, char *filename);

int	full_quit(t_wrap *wrap );
int	handle_keypress(int keycode, t_wrap *wrap);
int	handle_keyrelease(int keycode, t_wrap *wrap);

#endif
