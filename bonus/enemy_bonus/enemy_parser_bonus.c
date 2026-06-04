#include "../includes_bonus/cub_bonus.h"

static int	load_idle_textures(t_cub *cub)
{
	if (!load_single_texture(cub, &cub->enemy_anims.idle[0],
			"assets/Soldier/front.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.idle[1],
			"assets/Soldier/left.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.idle[2],
			"assets/Soldier/still-back1780564653.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.idle[3],
			"assets/Soldier/still-front-right1780564653.xpm"))
		return (0);
	return (1);
}

static int	load_walk_textures(t_cub *cub)
{
	if (!load_single_texture(cub, &cub->enemy_anims.walk[0],
			"assets/Soldier/front21780564653.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.walk[1],
			"assets/Soldier/front31780564653.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.walk[2],
			"assets/Soldier/front41780564653.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.walk[3],
			"assets/Soldier/front-left11780564653.xpm"))
		return (0);
	return (1);
}

static int	load_attack_and_dead(t_cub *cub)
{
	if (!load_single_texture(cub, &cub->enemy_anims.attack[0],
			"assets/Soldier/aim1780564653.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.attack[1],
			"assets/Soldier/shoot1780564653.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.dead[0],
			"assets/Soldier/death11780564653.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.dead[1],
			"assets/Soldier/death21780564653.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.dead[2],
			"assets/Soldier/death31780564653.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.dead[3],
			"assets/Soldier/death41780564653.xpm"))
		return (0);
	if (!load_single_texture(cub, &cub->enemy_anims.dead[4],
			"assets/Soldier/death51780564653.xpm"))
		return (0);
	return (1);
}

int	load_enemy_textures(t_cub *cub)
{
	if (!load_idle_textures(cub))
		return (0);
	if (!load_walk_textures(cub))
		return (0);
	if (!load_attack_and_dead(cub))
		return (0);
	return (1);
}
