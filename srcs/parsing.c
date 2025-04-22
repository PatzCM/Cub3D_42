#include "../incs/cub3d.h"

bool	parse_map(t_data *data)
{
	int		row;
	int		col;
	bool	is_valid;

	is_valid = true;
	row = 0;
	col = 0;

	while (data->map.map[row])
	{
		while (data->map.map[row][col])
		{
			if (data->map.map[row][col + 1] == '\0')
			{
				if (data->map.map[row][col] != '1')
					is_valid = false;
				if (data->map.max_width < col)
					data->map.max_width = col;
			}
			col++;
		}
		row++;
	}
	return (is_valid);
}


static int	size_map(char *file)
{
	int fd;
	int i;
	char	*line;


	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	i = 0;
	line = get_next_line(fd);
	i++;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (close(fd), i);
}

void	copy_map(t_data *data, char *file)
{
	int		i;
	int		fd;
	char	*line;
	
	fd = open(file, O_RDONLY);
	i = size_map(file);
	printf("i = %d\n", i);
	data->map.map = (char **)malloc(sizeof(char *) * (i + 1));
	data->map.matrix = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (i++ <= data->map_data.line_position)
		line = get_next_line(fd);
	while (line)
	{
		data->map.map[i] = line;
		data->map.matrix[i] = line;
		printf("%s\n", data->map.map[i]);
		line = get_next_line(fd);
		i++;
	}
	data->map.map[i] = NULL;
	data->map.matrix[i] = NULL;
	close(fd);
}
