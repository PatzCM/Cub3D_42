#ifndef CUB3D_H
#define CUB3D_H

//---------------------------------------------------------------------------
// Includes
// ---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include "../libs/libft/libft.h"
#include "../libs/mlx/mlx.h"
#include <stdbool.h>

// -------------------------------------------------------------------------
// Macros
// -------------------------------------------------------------------------
#define TRUE 1
#define FALSE 0

//---------------------------------------------------------------------------
// Structures
// ---------------------------------------------------------------------------

typedef struct s_map
{
	int		max_width;
	int		max_height;
	char	**map;
	char	**matrix;
}	t_map;

typedef struct s_player
{
	int		x;
	int		y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_data
{
	int	player_count;
	t_map	map;
	t_player	player;

}
	t_data;


//---------------------------------------------------------------------------
// Function Prototypes
// ---------------------------------------------------------------------------
void	copy_map(t_data *data, int fd);
void	init_data(t_data *data);
bool	parse_map(t_data *data);


#endif
