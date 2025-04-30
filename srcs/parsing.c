#include "../incs/cub3d.h"

bool	parse_map(t_data *data)
{
	int		row;
	int		col;
	bool	is_valid;
	
	is_valid = FALSE;
	row = 0;
	col = 0;
	while (data->map.matrix[row][col] == '1')
	{
		while (data->map.matrix[row][col + 1] == '1')
		{
			data->map.matrix[row][col] = 2;
			col++;
		}
		while (data->map.matrix[row][col - 1] == '1' )
		{
			data->map.matrix[row][col] = 2;
			col--;
		}
		if (row < data->map.max_height && data->map.matrix[row + 1][col] == '1' )
		{
			data->map.matrix[row][col] = 2;
			row++;
			continue;
		}
		if (row > 0 && data->map.matrix[row - 1][col] == '1' )
		{
			data->map.matrix[row][col] = 2;
			row--;
			continue;
		}
		if (col > 0 && ((data->map.matrix[row][col -1] == 2 && data->map.matrix[row][col + 1] == '\0') 
			|| (data->map.matrix[row][col - 1] == '1' && data->map.matrix[row][col + 1] == '\0')))
		{
		 data->map.matrix[row][col] = 2;
		 col--;
		 	continue;
		 }
		if (data->map.matrix[row][col + 1] == 2 && data->map.matrix[row][col - 1] == '\0') 
			/*|| (data->map.matrix[row][col + 1] == '1' && data->map.matrix[row][col - 1] == '\0'))*/
		{
		 data->map.matrix[row][col] = 2;
		 col++;
		 continue;
		}
		else if ((data->map.matrix[row - 1][col] == 2 && row == 1 && col == 0) || (data->map.matrix[row][col] == 2 && row == 0 && col == 0))
			return (is_valid = TRUE);
		else
			break;
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
	data->map.max_height = i;
	data->map.map = malloc(sizeof(t_map) * i);
	data->map.matrix = malloc(sizeof(t_map) * i);
	i = -1;
	while (i++ <= data->map_data.line_position)
		line = get_next_line(fd);
	i = 0;
	while (line)
	{
		data->map.map[i] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
		data->map.matrix[i] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
		data->map.map[i] = line;
		data->map.matrix[i] = line;
		line = get_next_line(fd);
		i++;
	}
	data->map.map[i] = NULL;
	data->map.matrix[i] = NULL;
	close(fd);
}
