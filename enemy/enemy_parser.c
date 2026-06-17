#include "../includes/thedump.h"

static char *get_dir_name(int dir)
{
	if (dir == DIR_FRONT) return "front";
	if (dir == DIR_FRONT_RIGHT) return "front-right";
	if (dir == DIR_RIGHT) return "right";
	if (dir == DIR_BACK_RIGHT) return "back-right";
	if (dir == DIR_BACK) return "back";
	if (dir == DIR_BACK_LEFT) return "back-left";
	if (dir == DIR_LEFT) return "left";
	if (dir == DIR_FRONT_LEFT) return "front-left";
	return "front";
}

static int load_directional_anim(t_cub *cub, t_texture anim[8][ENEMY_WALK_FRAMES], 
								char *base_path, int frames)
{
	int d;
	int f;
	char path[256];

	d = 0;
	while (d < 8)
	{
		f = 0;
		while (f < frames)
		{
			ft_sprintf(path, "%s/%s%d.xpm", base_path, get_dir_name(d), f + 1);
			if (!load_single_texture(cub, &anim[d][f], path))
			{
				// Fallback to front if specific direction/frame fails
				ft_sprintf(path, "%s/front%d.xpm", base_path, f + 1);
				if (!load_single_texture(cub, &anim[d][f], path))
					return (0);
			}
			f++;
		}
		d++;
	}
	return (1);
}

static int load_soldier_textures(t_cub *cub)
{
	t_enemy_anims *a = &cub->enemy_anims[SOLDIER_TYPE];
	
	// Soldier has messed up names, hardcoding some or using what was there
	load_single_texture(cub, &a->idle[DIR_FRONT][0], "assets/Soldier/front.xpm");
	load_single_texture(cub, &a->walk[DIR_FRONT][0], "assets/Soldier/front21780564653.xpm");
	load_single_texture(cub, &a->walk[DIR_FRONT][1], "assets/Soldier/front31780564653.xpm");
	load_single_texture(cub, &a->walk[DIR_FRONT][2], "assets/Soldier/front41780564653.xpm");
	load_single_texture(cub, &a->walk[DIR_FRONT][3], "assets/Soldier/front.xpm");
	// Fill other directions with front for soldier to avoid crash if files are missing
	for (int d = 1; d < 8; d++) {
		for (int f = 0; f < 4; f++) a->walk[d][f] = a->walk[0][f];
		for (int f = 0; f < 4; f++) a->idle[d][f] = a->idle[0][0];
	}
	load_single_texture(cub, &a->attack[DIR_FRONT][0], "assets/Soldier/aim1780564653.xpm");
	load_single_texture(cub, &a->attack[DIR_FRONT][1], "assets/Soldier/shoot1780564653.xpm");
	load_single_texture(cub, &a->dead[0], "assets/Soldier/death11780564653.xpm");
	load_single_texture(cub, &a->dead[1], "assets/Soldier/death21780564653.xpm");
	load_single_texture(cub, &a->dead[2], "assets/Soldier/death31780564653.xpm");
	load_single_texture(cub, &a->dead[3], "assets/Soldier/death41780564653.xpm");
	load_single_texture(cub, &a->dead[4], "assets/Soldier/death51780564653.xpm");
	return (1);
}

static int load_dog_textures(t_cub *cub)
{
	t_enemy_anims *a = &cub->enemy_anims[DOG_TYPE];
	
	if (!load_directional_anim(cub, a->walk, "assets/dog", 4)) return (0);
	// Dog idle is same as walk[0]
	for (int d = 0; d < 8; d++) a->idle[d][0] = a->walk[d][0];
	
	load_single_texture(cub, &a->attack[DIR_FRONT][0], "assets/dog/bite1.xpm");
	load_single_texture(cub, &a->attack[DIR_FRONT][1], "assets/dog/bite2.xpm");
	load_single_texture(cub, &a->attack[DIR_FRONT][2], "assets/dog/bite3.xpm");
	load_single_texture(cub, &a->dead[0], "assets/dog/death1.xpm");
	load_single_texture(cub, &a->dead[1], "assets/dog/death2.xpm");
	load_single_texture(cub, &a->dead[2], "assets/dog/death3.xpm");
	return (1);
}

static int load_officer_textures(t_cub *cub)
{
	t_enemy_anims *a = &cub->enemy_anims[OFFICER_TYPE];
	
	if (!load_directional_anim(cub, a->walk, "assets/officer", 4)) return (0);
	for (int d = 0; d < 8; d++) a->idle[d][0] = a->walk[d][0];

	load_single_texture(cub, &a->attack[DIR_FRONT][0], "assets/officer/aim.xpm");
	load_single_texture(cub, &a->attack[DIR_FRONT][1], "assets/officer/shoot.xpm");
	load_single_texture(cub, &a->dead[0], "assets/officer/death1.xpm");
	load_single_texture(cub, &a->dead[1], "assets/officer/death2.xpm");
	load_single_texture(cub, &a->dead[2], "assets/officer/death3.xpm");
	load_single_texture(cub, &a->dead[3], "assets/officer/death4.xpm");
	load_single_texture(cub, &a->dead[4], "assets/officer/death5.xpm");
	return (1);
}

int	load_enemy_textures(t_cub *cub)
{
	if (!load_soldier_textures(cub)) return (0);
	if (!load_dog_textures(cub)) return (0);
	if (!load_officer_textures(cub)) return (0);
	return (1);
}
