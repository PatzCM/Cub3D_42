/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:07:43 by palexand          #+#    #+#             */
/*   Updated: 2025/04/19 21:27:37 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

bool	parse_textures(t_data *data, char *file)
{
	int fd;
	char	*line;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strnstr(line, "NO", 2))
			data->map_data.NO = ft_strdup(line + 3);
		else if (ft_strnstr(line, "SO", 2))
			data->map_data.SO = ft_strdup(line + 3);
		else if (ft_strnstr(line, "WE", 2))
			data->map_data.WE = ft_strdup(line + 3);
		else if (ft_strnstr(line, "EA", 2))
			data->map_data.EA = ft_strdup(line + 3);
		else if (ft_strnstr(line, "F", 1))
			data->map_data.F = ft_strdup(line + 2);
		else if (ft_strnstr(line, "C", 1))
			data->map_data.C = ft_strdup(line + 2);
		line = get_next_line(fd);
	}
	return (true);
}

void	rgb_int(t_data *data)
{
	int i;
	int j;
	char **rgb;

	i = 0;
	j = 0;
	if (data->map_data.F)
	{
		rgb = ft_split(data->map_data.F, ',');
		while (rgb[i])
			i++;
		data->map_data.color_f = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]);
	}
	if (data->map_data.C)
	{
		rgb = ft_split(data->map_data.C, ',');
		while (rgb[j])
			j++;
		data->map_data.color_c = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]);
	}
}

void parse_cub_file(char *extension, char *file)
{
	int i;
	i = 0;
	while (file[i] != '.')
		i++;
	if (ft_strncmp(&file[i], extension, 5) != 0 || i == 0)
	{
		write(1, "Error\nInvalid file extension\n", 31);
		exit(1);
	}
	printf("File extension is valid\n");
}
