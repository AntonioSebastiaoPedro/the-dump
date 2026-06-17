#include "../includes/thedump.h"

void	draw_skybox(t_cub *cub)
{
	int		x;
	int		y;
	int		sky_x;
	int		sky_y;
	double	angle;
	unsigned int	color;

	if (!cub->config->c_tex || !cub->textures->skybox.img)
		return ;
	
	// atan2(dir_y, dir_x) gives the angle in radians [-PI, PI]
	angle = atan2(cub->player->dir_y, cub->player->dir_x);
	if (angle < 0)
		angle += 2 * M_PI;
	
	// ratio is [0, 1] based on rotation
	double ratio = angle / (2 * M_PI);
	int offset_x = (int)(ratio * cub->textures->skybox.width);

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			// Calculate sky_x with wrapping
			sky_x = (offset_x + (x * cub->textures->skybox.width / WIDTH))
				% cub->textures->skybox.width;
			
			// Calculate sky_y (top half of screen maps to full skybox height)
			sky_y = (y * cub->textures->skybox.height) / (HEIGHT / 2);
			
			color = get_texture_color(&cub->textures->skybox, sky_x, sky_y);
			ft_put_pixel(cub, x, y, color);
			x++;
		}
		y++;
	}
}