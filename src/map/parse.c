# include "../../include/conway.h"

static void	free_split(char **split)
{
	int	pos;

	pos = 0;
	while (split[pos])
		free(split[pos++]);
	free(split);
}

int	get_width(char *line)
{
	int	width = 0;
	char	**split;

	split = ft_split(line, ' ');
	while (split[width])
		width++;
	free_split(split);
	return (width);
}

void	get_dim(t_map *map, int fd)
{
	char	*line;

	map->height = 0;
	line = get_next_line(fd);
	map->width = get_width(line);
	while (line)
	{
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

void	init_map(t_map *map)
{
	size_t	i;
	size_t	j;

	map->cell = (bool **)malloc(sizeof(bool *) * map->height);
	i = 0;
	while (i < map->height)
	{
		map->cell[i] = (bool *)malloc(sizeof(bool) * map->width);
		j = 0;
		while (j < map->width)
		{
			map->cell[i][j] = false;
			j++;
		}
		i++;
	}
}

void	fill_line(int width, bool *line, char **split)
{
	int	i;

	i = 0;
	while (i < width && split[i])
	{
		line[i] = ft_atoi(split[i]);
		i++;
	}
}

void	parse_map(t_map	*map, char *filename)
{
	int		fd;
	int		i;
	char	*line;
	char	**split;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		split = ft_split(line, ' ');
		fill_line(map->width, map->cell[i], split);
		free_split(split);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	free(line);
}

bool	read_from_file(t_map *map, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
	{
		perror("");
		return (false);
	}
	get_dim(map, fd);
	close(fd);
	init_map(map);
	parse_map(map, filename);
	return (true);
}
