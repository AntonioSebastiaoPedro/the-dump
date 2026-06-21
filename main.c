#include "includes/thedump.h"
#include <X11/Xlib.h>

int	main(int ac, char **av)
{
	t_cub	*cub;

	XInitThreads();

	cub = parse_cub(ac, av);
	if (!cub)
		return (1);
	cub->mlx = init_mlx();
	if (!cub->mlx)
		return (free_cub(cub), 1);
	cub->mouse.center_x = WIDTH / 2;
	cub->mouse.center_y = HEIGHT / 2;
	cub->state = LOADING;
	cub->difficulty = DIFF_HARD;
	init_loading(cub, &cub->loading, cub->mlx->mlx);

	// Load and scale UI textures needed for transitions and menu
	if (!load_single_texture(cub, &cub->menu.loading_img, LOADING_IMG))
		return (free_cub(cub), 1);
	scale_texture(cub, &cub->menu.loading_img, WIDTH, HEIGHT);
	if (!load_single_texture(cub, &cub->menu.menu_img, MENU_IMG))
		return (free_cub(cub), 1);
	scale_texture(cub, &cub->menu.menu_img, WIDTH, HEIGHT);
	if (!load_single_texture(cub, &cub->menu.about_img, ABOUT_IMG))
		return (free_cub(cub), 1);
	scale_texture(cub, &cub->menu.about_img, WIDTH, HEIGHT);
	if (!load_single_texture(cub, &cub->menu.victory_img, VICTORY_IMG))
		return (free_cub(cub), 1);
	scale_texture(cub, &cub->menu.victory_img, WIDTH, HEIGHT);
	if (!load_single_texture(cub, &cub->menu.game_over_img, GAME_OVER_IMG))
		return (free_cub(cub), 1);
	scale_texture(cub, &cub->menu.game_over_img, WIDTH, HEIGHT);
	start_loader_thread(cub);
	
	/* ===== INITIALIZE THREADING SYSTEM ===== */
	pthread_mutex_init(&cub->render_mutex, NULL);
	cub->raycast_pool = init_raycast_pool(cub);
	if (!cub->raycast_pool)
	{
		ft_fprintf_fd(2, "Erro ao inicializar threads!\n");
		return (free_cub(cub), 1);
	}
	
	cub->player_hp = PLAYER_MAX_HP;
	cub->show_mira = false;
	cub->crosshair.scale = 1.0f;
	cub->crosshair.color = GREEN;
	cub->crosshair.enabled = true;
	hook_close(cub);
	mlx_hook(cub->mlx->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->mlx->win, 3, 1L << 1, key_release, cub);
	mlx_mouse_hook(cub->mlx->win, mouse_hook, cub);
	mlx_loop_hook(cub->mlx->mlx, loop_hook, cub);
	(mlx_loop(cub->mlx->mlx), free_cub(cub));
	return (0);
}