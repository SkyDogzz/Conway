#include "../../include/conway.h"

void	free_map(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->height)
	{
		free(map->cell[i]);
		i++;
	}
	free(map->cell);
}

int	full_quit(t_wrap *wrap)
{
	mlx_destroy_image(wrap->mlx_ptr, wrap->data.img);
	mlx_destroy_window(wrap->mlx_ptr, wrap->mlx_win);
	mlx_destroy_display(wrap->mlx_ptr);
	free(wrap->mlx_ptr);
	free_map(&wrap->map);
	exit(0);
}

int	handle_keypress(int keycode, t_wrap *wrap)
{
	if (keycode == KEYCODE_Q || keycode == KEYCODE_ESC)
		full_quit(wrap);
	update_img(wrap);
	(void) keycode;
	(void) wrap;
	return (0);
}

int	handle_keyrelease(int keycode, t_wrap *wrap)
{
	(void) keycode;
	(void) wrap;
	return (0);
}
