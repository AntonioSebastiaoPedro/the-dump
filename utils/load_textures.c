#include "../includes/thedump.h"

int	load_single_texture(t_cub *cub, t_texture *tex, const char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx->mlx, (char *)path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		ft_putendl_fd("Error\nNão foi possível carregar alguma textura", 2);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	increment_loader(cub);
	return (1);
}

int	load_weapon(t_cub *cub, t_weapon *weapon,
		const char *paths[WEAPON_STATES][WEAPON_FRAMES])
{
	int			state;
	int			frame;

	state = 0;
	while (state < WEAPON_STATES)
	{
		frame = 0;
		while (frame < WEAPON_FRAMES)
		{
			if (paths[state][frame] == NULL)
			{
				frame++;
				continue ;
			}
			if (!load_single_texture(cub
					, &weapon->frames[state][frame], paths[state][frame]))
				return (0);
			frame++;
		}
		state++;
	}
	weapon->state = WEAPON_IDLE;
	weapon->current_frame = 0;
	weapon->frame_timer = 0;
	return (set_weapon_state(weapon, WEAPON_IDLE), 1);
}

int	load_weapon_textures(t_cub *cub)
{
	const char	*rev_paths[WEAPON_STATES][WEAPON_FRAMES] = {
	{"assets/weapon/idle/idle1.xpm", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{"assets/weapon/move/move1.xpm", "assets/weapon/move/move2.xpm", "assets/weapon/move/move3.xpm", "assets/weapon/move/move4.xpm", "assets/weapon/move/move5.xpm", "assets/weapon/move/move6.xpm", "assets/weapon/move/move7.xpm", NULL, NULL, NULL, NULL, NULL, NULL},
	{"assets/weapon/shot/frame1.xpm", "assets/weapon/shot/frame2.xpm", "assets/weapon/shot/frame3.xpm", "assets/weapon/shot/frame4.xpm", "assets/weapon/shot/frame5.xpm", "assets/weapon/shot/frame6.xpm", "assets/weapon/shot/frame7.xpm", "assets/weapon/shot/frame8.xpm", "assets/weapon/shot/frame9.xpm", NULL, NULL, NULL, NULL}
	};
	const char	*rifle_paths[WEAPON_STATES][WEAPON_FRAMES] = {
	{
		"assets/BoltRifle/idle/1.xpm",
		NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL
	},
	{
		"assets/BoltRifle/move/1.xpm",
		"assets/BoltRifle/move/2.xpm",
		"assets/BoltRifle/move/3.xpm",
		"assets/BoltRifle/move/4.xpm",
		"assets/BoltRifle/move/5.xpm",
		"assets/BoltRifle/move/6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL
	},
	{
		"assets/BoltRifle/shot/1.xpm",
		"assets/BoltRifle/shot/2.xpm",
		"assets/BoltRifle/shot/3.xpm",
		"assets/BoltRifle/shot/4.xpm",
		"assets/BoltRifle/shot/5.xpm",
		"assets/BoltRifle/shot/6.xpm",
		"assets/BoltRifle/shot/7.xpm",
		"assets/BoltRifle/shot/8.xpm",
		"assets/BoltRifle/shot/9.xpm",
		"assets/BoltRifle/shot/10.xpm",
		"assets/BoltRifle/shot/11.xpm",
		"assets/BoltRifle/shot/12.xpm",
		"assets/BoltRifle/shot/13.xpm",
	}
	};
	const char	*plasma_paths[WEAPON_STATES][WEAPON_FRAMES] = {
	{
		"assets/PlasmaCaster/idle/1.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL
	},
	{
		"assets/PlasmaCaster/move/1.xpm",
		"assets/PlasmaCaster/move/2.xpm",
		"assets/PlasmaCaster/move/3.xpm",
		"assets/PlasmaCaster/move/4.xpm",
		"assets/PlasmaCaster/move/5.xpm",
		"assets/PlasmaCaster/move/6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL
	},
	{
		"assets/PlasmaCaster/shot/1.xpm",
		"assets/PlasmaCaster/shot/2.xpm",
		"assets/PlasmaCaster/shot/3.xpm",
		"assets/PlasmaCaster/shot/4.xpm",
		"assets/PlasmaCaster/shot/5.xpm",
		"assets/PlasmaCaster/shot/6.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL
	}
	};

	cub->weapons[WEAPON_REVOLVER].type = WEAPON_REVOLVER;
	cub->weapons[WEAPON_REVOLVER].max_ammo = REVOLVER_MAX_AMMO;
	cub->weapons[WEAPON_REVOLVER].current_ammo = CURRENT_AMMO;
	cub->weapons[WEAPON_REVOLVER].reserve_ammo = REVOLVER_MAX_AMMO;
	load_single_texture(cub, &cub->weapons[WEAPON_REVOLVER].hud_icon, "assets/weapon/idle/idle1.xpm");

	cub->weapons[WEAPON_RIFLE].type = WEAPON_RIFLE;
	cub->weapons[WEAPON_RIFLE].max_ammo = RIFLE_MAX_AMMO;
	cub->weapons[WEAPON_RIFLE].current_ammo = CURRENT_AMMO;
	cub->weapons[WEAPON_RIFLE].reserve_ammo = RIFLE_MAX_AMMO;
	load_single_texture(cub, &cub->weapons[WEAPON_RIFLE].hud_icon, "assets/BoltRifle/idle/1.xpm");

	cub->weapons[WEAPON_PLASMA].type = WEAPON_PLASMA;
	cub->weapons[WEAPON_PLASMA].max_ammo = PLASMA_MAX_AMMO;
	cub->weapons[WEAPON_PLASMA].current_ammo = CURRENT_AMMO;
	cub->weapons[WEAPON_PLASMA].reserve_ammo = PLASMA_MAX_AMMO;
	load_single_texture(cub, &cub->weapons[WEAPON_PLASMA].hud_icon, "assets/PlasmaCaster/idle/1.xpm");

	if (!load_weapon(cub, &cub->weapons[WEAPON_REVOLVER], rev_paths))
		return (0);
	if (!load_weapon(cub, &cub->weapons[WEAPON_RIFLE], rifle_paths))
		return (0);
	if (!load_weapon(cub, &cub->weapons[WEAPON_PLASMA], plasma_paths))
		return (0);
	cub->current_weapon_index = WEAPON_RIFLE;
	cub->current_weapon = &cub->weapons[WEAPON_REVOLVER];
	return (1);
}

int	load_door_textures(t_cub *cub)
{
	const char	*paths[DOOR_FRAMES] = {
		"assets/door/door0.xpm",
		"assets/door/door1.xpm",
		"assets/door/door2.xpm",
		"assets/door/door3.xpm",
		"assets/door/door4.xpm",
		"assets/door/door5.xpm",
		"assets/door/door6.xpm",
		"assets/door/door7.xpm",
		"assets/door/door8.xpm",
	};
	int			i;

	i = 0;
	while (i < DOOR_FRAMES)
	{
		if (!load_single_texture(cub, &cub->door_frames[i], paths[i]))
			return (0);
		i++;
	}
	return (1);
}

int	load_door_blue_textures(t_cub *cub)
{
	const char	*paths[DOOR_FRAMES] = {
		"assets/door_blue/door0.xpm",
		"assets/door_blue/door1.xpm",
		"assets/door_blue/door2.xpm",
		"assets/door_blue/door3.xpm",
		"assets/door_blue/door4.xpm",
		"assets/door_blue/door5.xpm",
		"assets/door_blue/door6.xpm",
		"assets/door_blue/door7.xpm",
		"assets/door_blue/door8.xpm",
	};
	int			i;

	i = 0;
	while (i < DOOR_FRAMES)
	{
		if (!load_single_texture(cub, &cub->door_blue_frames[i], paths[i]))
			return (0);
		i++;
	}
	return (1);
}

int	load_textures(t_cub *cub)
{
	if (!load_single_texture(cub, &cub->textures->no, cub->config->no))
		return (0);
	if (!load_single_texture(cub, &cub->textures->so, cub->config->so))
		return (0);
	if (!load_single_texture(cub, &cub->textures->we, cub->config->we))
		return (0);
	if (!load_single_texture(cub, &cub->textures->ea, cub->config->ea))
		return (0);
	if (!load_floor_ceiling_texture(cub))
		return (0);
	if (!load_weapon_textures(cub))
		return (0);
	if (!load_door_textures(cub))
		return (0);
	if (!load_door_blue_textures(cub))
		return (0);
	if (!load_item_textures(cub))
		return (0);
	init_items(cub);
	if (cub->config->c_tex && !load_single_texture(cub, &cub->textures->skybox, cub->config->c_tex))
		return (0);
	return (1);
}