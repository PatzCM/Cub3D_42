/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:11:18 by palexand          #+#    #+#             */
/*   Updated: 2025/05/24 22:11:21 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

static bool	check_spaces(char **matrix)
{
	int i;
	int j;
	
	i = -1;
	while (matrix[++i])
	{
		j = 0;
		while (matrix[i][j] == ' ')
			j++;
		while (matrix[i][j])
		{
			if (matrix[i][j] == ' ')
				if (matrix[i][j - 1] != '1' && matrix[i][j] - 1 != ' ' 
			 	&& matrix[i][j + 1] && matrix[i][j + 1] != ' ' 
				&& matrix[i][j + 1] != '1'
			 	&& matrix[i + 1][j] && matrix[i + 1][j] != ' ' 
				&& matrix[i + 1][j] != '1'
			 	&& matrix[i - 1] && matrix[i - 1][j] != ' ' 
				&& matrix[i - 1][j] != '1')
						return (printf("Error\n invalid map spaces"), FALSE);
			j++;
		}
	}
	return (TRUE);
}

static bool check_map_borders(char *line)
{
	int i;
	int j;
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strlen(line) < 3 && line[i] != '1')
		return (FALSE);
	j = ft_strlen(line) - 1;
	while (line[j] && line[j] == ' ')
		j--;
	if (line[j] != '1' || (ft_strlen(line) == 1 && line[i] != '1'))
return FALSE;
	return (TRUE);

}

static bool check_map_walls(char **map, int i, int j)
{
	if (i > 1 && ft_strlen(map[i]) > ft_strlen(map[i + 1]) 
		&& j >= ft_strlen(map[i - 1]) && map[i][j] && map[i][j] != '1')
		return (FALSE);
	if ( i > 0 && map[i + 1] != NULL && ft_strlen(map[i]) > ft_strlen(map[i - 1]) 
		 && j >= ft_strlen(map[i + 1]) && map[i][j] && map[i][j] != '1')
		return (FALSE);
	if (!map[i][j] || (i == 0 && map[i + 1] == NULL))
		if (map[i][j] != '1' || map[i][j] != ' ')
			return (FALSE);
	return (TRUE);
}

static bool check_elements(char **map)
{
	int i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0' 
				&& map[i][j] != 'N' && map[i][j] != 'S' 
				&& map[i][j] != 'E' && map[i][j] != 'W')
				return (FALSE);
			j++;
		}
	}
	return (TRUE);
}

// @brief	Function to parse the map from the data structure
bool	parse_map(char **map)
{
	int i;
	int j;
	
	i = -1;
	j = -1;
	
	if (check_spaces(map) == FALSE || check_elements(map) == FALSE)
		return (FALSE);

	while (map[++i])
	{
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				j++;
			if (!map[i][j])
				break;
			if (check_map_borders(map[i]) == FALSE || check_map_walls(map, i, j) == FALSE)
				return(printf("Error\n invalid map borders or walls\n"), FALSE);
			j++;
		}
	}
	return (TRUE);
}

// @brief	Function to check if the map is valid
// @param	data	Pointer to the data structure
// @return	Returns true if the map is valid, false otherwise
//@note i = -2 because of the first and last line

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
	i = -2;
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
	i = (size_map(file) - data->map_data.line_position);
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
