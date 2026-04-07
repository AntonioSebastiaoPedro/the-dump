/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:40:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/07 11:40:00 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/**
 * @brief Initializes the menu selection state.
 */
void init_menu(t_cub *cub)
{
    cub->menu.selected = 0;
    cub->menu.total = 3;
}

/**
 * @brief Logic for menu navigation and highlighting.
 * Here we can add animations like blinking if needed.
 */
void update_menu(t_cub *cub)
{
    // For now, logic is handled in handle_menu_input
    // but we can add blink effects here using a frame counter if desired.
    (void)cub;
}

/**
 * @brief Renders the menu options on the window.
 */
void render_menu(t_cub *cub)
{
    int y;
    int color;
    int i;
    int j;

    // Optimized background rendering
    i = 0;
    while (i < cub->mlx->width)
    {
        j = 0;
        while (j < cub->mlx->height)
        {
            put_pixel(cub, i, j, 0x1A1A1A);
            j++;
        }
        i++;
    }
    
    // Put background image to window before drawing strings
    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);

    y = cub->mlx->height / 2 - 50;

    // PLAY
    color = (cub->menu.selected == 0) ? 0x00FF00 : 0xFFFFFF;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, cub->mlx->width / 2 - 30, y, color, 
        (cub->menu.selected == 0) ? "> PLAY" : "  PLAY");

    // ABOUT
    y += 40;
    color = (cub->menu.selected == 1) ? 0x00FF00 : 0xFFFFFF;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, cub->mlx->width / 2 - 30, y, color, 
        (cub->menu.selected == 1) ? "> ABOUT" : "  ABOUT");

    // QUIT
    y += 40;
    color = (cub->menu.selected == 2) ? 0x00FF00 : 0xFFFFFF;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, cub->mlx->width / 2 - 30, y, color, 
        (cub->menu.selected == 2) ? "> QUIT" : "  QUIT");
}

/**
 * @brief Renders the ABOUT screen information.
 */
void render_about(t_cub *cub)
{
    int y = 100;
    int margin = 50;
    int i;
    int j;

    // Optimized background rendering
    i = 0;
    while (i < cub->mlx->width)
    {
        j = 0;
        while (j < cub->mlx->height)
        {
            put_pixel(cub, i, j, 0x000000);
            j++;
        }
        i++;
    }

    // Put background image to window before drawing strings
    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);

    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0x00FF00, "Projecto: This project has been created as part");
    y += 20;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0x00FF00, "of the 42 curriculum by Paulo Cardoso (paulcard),");
    y += 20;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0x00FF00, "Antonio Amandio (aamandio)");
    
    y += 40;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0xFFFFFF, "Descricao:");
    y += 20;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0xCCCCCC, "Cub3D e um projeto baseado em raycasting que simula");
    y += 20;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0xCCCCCC, "um ambiente 3D a partir de um mapa 2D.");
    y += 40;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0xCCCCCC, "O jogador pode se movimentar em um mundo virtual,");
    y += 20;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0xCCCCCC, "onde paredes sao renderizadas em tempo real,");
    y += 20;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0xCCCCCC, "criando uma sensacao de profundidade.");
    y += 40;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0xFFFFFF, "O projeto explora conceitos como:");
    y += 20;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0x00AAFF, "- trigonometria");
    y += 20;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0x00AAFF, "- manipulacao de pixels");
    y += 20;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0x00AAFF, "- renderizacao grafica");
    y += 20;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0x00AAFF, "- estruturas de dados");
    y += 20;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, margin, y, 0x00AAFF, "- game loop");

    y += 80;
    mlx_string_put(cub->mlx->mlx, cub->mlx->win, cub->mlx->width / 2 - 100, y, 0xAAAAAA, "Pressione ESC para voltar ao MENU");
}

/**
 * @brief Handles menu input for navigation and selection.
 */
void handle_menu_input(int key, t_cub *cub)
{
    if (cub->state == MENU)
    {
        if (key == KEY_UP || key == KEY_W)
        {
            cub->menu.selected--;
            if (cub->menu.selected < 0)
                cub->menu.selected = cub->menu.total - 1;
        }
        else if (key == KEY_DOWN || key == KEY_S)
        {
            cub->menu.selected++;
            if (cub->menu.selected >= cub->menu.total)
                cub->menu.selected = 0;
        }
        else if (key == KEY_ENTER)
        {
            if (cub->menu.selected == 0) // PLAY
                cub->state = GAME;
            else if (cub->menu.selected == 1) // ABOUT
                cub->state = ABOUT;
            else if (cub->menu.selected == 2) // QUIT
            {
                free_cub(cub);
                exit(0);
            }
        }
    }
    else if (cub->state == ABOUT)
    {
        if (key == ESC)
            cub->state = MENU;
    }
}
