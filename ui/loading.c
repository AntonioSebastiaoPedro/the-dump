/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:27:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/07 10:27:00 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
 * @brief Initializes the loading screen structure.
 * 
 * @param loading Pointer to the loading struct.
 * @param mlx Pointer to the MLX structure.
 */
void init_loading(t_loading *loading, void *mlx)
{
    (void)mlx;
    loading->progress = 0;
    loading->max_progress = 100;
    loading->frame_count = 0;
    loading->logo = NULL;
    loading->background = NULL;
}

/**
 * @brief Updates the loading progress.
 * 
 * @param loading Pointer to the loading struct.
 */
void update_loading(t_loading *loading)
{
    if (loading->progress < loading->max_progress)
    {
        loading->frame_count++;
        if (loading->frame_count >= 8) // Change this value to adjust speed (higher = slower)
        {
            loading->progress += 1;
            loading->frame_count = 0;
        }
    }
}

/**
 * @brief Checks if the loading is complete.
 * 
 * @param loading Pointer to the loading struct.
 * @return int 1 if complete, 0 otherwise.
 */
int is_loading_complete(t_loading *loading)
{
    return (loading->progress >= loading->max_progress);
}

/**
 * @brief Draws a filled rectangle on the screen.
 * 
 * @param cub Pointer to the cub struct.
 * @param x Start X coordinate.
 * @param y Start Y coordinate.
 * @param w Width of the rectangle.
 * @param h Height of the rectangle.
 * @param color Color of the rectangle.
 */
static void draw_rectangle(t_cub *cub, int x, int y, int w, int h, int color)
{
    int i;
    int j;

    i = 0;
    while (i < h)
    {
        j = 0;
        while (j < w)
        {
            put_pixel(cub, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

/**
 * @brief Renders the loading screen.
 * 
 * @param game Pointer to the game (t_cub) struct.
 */
void render_loading(t_cub *game)
{
    int bar_width = 400;
    int bar_height = 30;
    int x = (game->mlx->width - bar_width) / 2;
    int y = (game->mlx->height - bar_height) / 2;
    int filled_width = (game->loading.progress * bar_width) / game->loading.max_progress;
    char progress_text[20];

    // Clear background (optional, could be a specific color)
    draw_rectangle(game, 0, 0, game->mlx->width, game->mlx->height, BLACK);

    // Draw background bar (border/empty)
    draw_rectangle(game, x - 2, y - 2, bar_width + 4, bar_height + 4, WHITE);
    draw_rectangle(game, x, y, bar_width, bar_height, GRAY);

    // Draw filled bar
    draw_rectangle(game, x, y, filled_width, bar_height, GREEN);

    ft_sprintf(progress_text, "Loading... %d%%", game->loading.progress);
    mlx_string_put(game->mlx->mlx, game->mlx->win, x + (bar_width / 2) - 40, y + bar_height + 30, WHITE, progress_text);
    
    // Put image to window
    mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->mlx->img, 0, 0);
}
