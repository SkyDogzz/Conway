#ifndef CONWAY_H
#define CONWAY_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../.minilibx-linux/mlx.h"
#include "../libft/include/libft.h"
#include "get_next_line.h"

typedef struct s_point {
	int x;
	int y;
} t_point;

typedef struct s_line {
	t_point p1;
	t_point p2;
} t_line;

typedef struct s_data {
	void *img;
	char *addr;
	int	  bits_per_pixel;
	int	  line_length;
	int	  endian;
} t_data;

typedef struct s_map {
	size_t width;
	size_t height;
	bool **cell;
} t_map;

typedef struct s_wrap {
	void  *mlx_ptr;
	void  *mlx_win;
	t_data data;
	t_map  map;
	int	   auto_speed;
	bool   auto_mode;
} t_wrap;

typedef enum e_keycode {
	KEYCODE_SPACE = 32,
	KEYCODE_Q = 113,
	KEYCODE_ESC = 65307,
	KEYCODE_LEFT = 65361,
	KEYCODE_UP = 65362,
	KEYCODE_RIGHT = 65363,
	KEYCODE_DOWN = 65364
} t_keycode;

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define CELL_SIZE 20

bool read_from_file(t_map *map, char *filename);

void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void update_img(t_wrap *wrap);

int	 full_quit(t_wrap *wrap);
int	 handle_keypress(int keycode, t_wrap *wrap);
int	 handle_keyrelease(int keycode, t_wrap *wrap);
void draw_grid(t_wrap *wrap);

int	 count_neighbors(t_map *map, int x, int y);
void next_generation(t_map *map);
void clear_image(t_data *data);

#endif
