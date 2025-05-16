
#ifndef CUBE_H
# define CUBE_H

# define mapWidth 24
# define mapHeight 24
# define screenWidth 640
# define screenHeight 480

/*============================================================================#
#                                 Libraries                                   #
#============================================================================*/

#include <math.h>
# include <X11/keysym.h>
#include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

/*============================================================================#
#                                 Structs                                     #
#============================================================================*/

typedef struct s_data
{
	int **worldmap;
	void	*mlx;
	void	*win;
	double	pos_X;
	double	pos_Y;
	double	plane_X;
	double	plane_Y;
	double	dir_vec_X;
	double	dir_vec_Y;
	double	curr_time;
	double	old_time;
	t_calc_vars *vars;
}	t_data;

typedef struct s_calc_vars
{
	double	camera_X;
	double	win_w;
	double	ray_DirX;
	double	ray_DirY;
	int		mapX;
	int		mapY;
	double	side_X;
	double	side_Y;
	double	next_X;
	double	next_Y;
	int		dir_stepX;
	int		dir_stepY;
	int		hit;
	int		side_hit;
}	t_calc_vars;

/*============================================================================#
#                                 Functions                                   #
#============================================================================*/

//inicializacion
void	data_ini(t_data *data);
void	window_ini(t_data *data);

//inputs
void	handle_inputs(t_data *data);

//calculations
void	raycaster(t_data *data);
void	calculate_ray_Dir(t_data *data);

//memory
int		ft_exit(t_data *data);



#endif
