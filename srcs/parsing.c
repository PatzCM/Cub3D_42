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
				else if (data->map.max_width < col)
					data->map.max_width = col;
			}
			col++;
		}
		if (data->map.map[row + 1][col] == '\0')
		{
			if (data->map.map[row + 1][col] != '1')
				is_valid = false;
			else if (data->map.max_height < row)
				data->map.max_height = row;
		}
		row++;
	}
	return (is_valid);
}

void	copy_map(t_data *data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		data->map.map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	/*data->map.map[i] = ft_strdup(NULL);*/
}
