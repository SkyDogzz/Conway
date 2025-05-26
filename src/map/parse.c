#include "../../include/conway.h"

static void free_split(char **split) {
	int pos;

	pos = 0;
	while (split[pos])
		free(split[pos++]);
	free(split);
}

int get_width(char *line) {
	int	   width = 0;
	char **split;

	split = ft_split(line, ' ');
	while (split[width])
		width++;
	free_split(split);
	return (width);
}

void get_dim(t_wrap *wrap, int fd) {
	char *line;

	wrap->map.height = 0;
	line = get_next_line(fd);
	wrap->map.width = get_width(line);
	while (line) {
		wrap->map.height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}


void init_map(t_wrap *wrap) {
	size_t i, j;

	size_t padded_height = wrap->map.height + 2 * wrap->blank_cell;
	size_t padded_width = wrap->map.width + 2 * wrap->blank_cell;

	wrap->map.cell = (bool **)calloc(padded_height, sizeof(bool *));
	i = 0;
	while (i < padded_height) {
		wrap->map.cell[i] = (bool *)calloc(padded_width, sizeof(bool));
		j = 0;
		while (j < padded_width) {
			wrap->map.cell[i][j] = false;
			j++;
		}
		i++;
	}

	wrap->map.height = padded_height;
	wrap->map.width = padded_width;
}

void fill_line(t_wrap *wrap, int y, char **split) {
	int x = 0;
	while (x < wrap->map.width && split[x]) {
		wrap->map.cell[y][wrap->blank_cell + x] = ft_atoi(split[x]);
		x++;
	}
}

void parse_map(t_wrap *wrap, char *filename) {
	int	   fd;
	int	   i;
	char  *line;
	char **split;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	i = wrap->blank_cell;
	while (line) {
		split = ft_split(line, ' ');
		fill_line(wrap, i, split);
		free_split(split);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	free(line);
}

bool read_from_file(t_wrap *wrap, char *filename) {
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (false);
	get_dim(wrap, fd);
	close(fd);
	init_map(wrap);
	parse_map(wrap, filename);
	return (true);
}

bool ft_parse_choice(t_wrap *wrap, char **argv) {
	int width;
	int height;

	if (!strict_atoi(argv[1], &width) || !strict_atoi(argv[2], &height))
		return false;
	wrap->map.height = height;
	wrap->map.width = width;
	init_map(wrap);
	return true;
}
