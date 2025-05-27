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
#include <time.h>
#include <sys/time.h>

#include "../.minilibx-linux/mlx.h"
#include "../libft/include/argp_simple.h"
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
	int	   width;
	int	   height;
	bool **cell;
} t_map;

#define DEFAULT_WINDOW_WIDTH 1600
#define DEFAULT_WINDOW_HEIGHT 900
#define DEFAULT_CELL_SIZE 10
#define DEFAULT_BLANK_CELL 100
#define DEFAULT_CELL_OFFSET 1
#define DEFAULT_TARGET_FPS 10
#define DEFAULT_DISPLAY_GRID 1

typedef struct s_wrap {
	void  *mlx_ptr;
	void  *mlx_win;
	t_data data;
	t_map  map;
	bool   run;
	int	   target_fps;
	int	   real_fps;
	bool   auto_mode;
	int	   window_width;
	int	   window_height;
	int	   cell_size;
	int	   blank_cell;
	int	   cell_offset;
	bool   display_grid;
	bool   random;
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

typedef struct s_option {
	char *name;
	char *description;
} t_option;

static t_option OPTION[] = {{"--help", "Display this help message"},
							{"--random", "Randomize cell placement"},
							{"--no-grid", "Hide the grid overlay"},
							{"--window-width=SIZE", "Set the window width to SIZE (in pixels)"},
							{"--window-height=SIZE", "Set the window height to SIZE (in pixels)"},
							{"--cell-size=SIZE", "Set the size of each cell in pixels"},
							{"--blank-cell=VALUE", "Set the value representing an empty cell"},
							{"--cell-offset=VALUE", "Set the space between cells (in pixels)"},
							{"--target-fps=FPS", "Set the target frames per second"},
							{0}};

bool read_from_file(t_wrap *wrap, char *filename);
bool ft_parse_choice(t_wrap *wrap, char **argv);
void init_map(t_wrap *wrap);

void my_mlx_pixel_put(t_wrap *wrap, int x, int y, int color);
void update_img(t_wrap *wrap);

int	 full_quit(t_wrap *wrap);
int	 handle_keypress(int keycode, t_wrap *wrap);
int	 handle_keyrelease(int keycode, t_wrap *wrap);
int	 handle_mouse_event(int keycode, int x, int y, t_wrap *wrap);
void get_grid_size(t_wrap *wrap, int *height, int *width);
void get_offsets(t_wrap *wrap, int height, int width, int *offsetX, int *offsetY);
void draw_grid(t_wrap *wrap);

int	 count_neighbors(t_map *map, int x, int y);
void next_generation(t_map *map);
void clear_image(t_wrap *wrap);

bool strict_atoi(const char *s, int *result);

#endif
