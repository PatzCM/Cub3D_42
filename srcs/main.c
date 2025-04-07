#include "../incs/cub3d.h"

int	main(int ac, char **av)
{
	int		fd;
	t_data	*data;


	if (ac != 2)
		return (write(1, "Error\n", 6), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (write(1, "Error\n", 6), 1);
	init_data(data);
	copy_map(data, fd);
	if (parse_map(data) == false)
		return (write(1, "Error\n", 6), 1);

}
