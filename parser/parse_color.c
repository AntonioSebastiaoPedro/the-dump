/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-18 14:04:24 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-18 14:04:24 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int	parse_color(const char *line, t_game *game)
{
	char	**rgb;
	int		r, g, b;
	char	id;

	printf("[COLOR] %s", line);

	// 1. validar identificador
	if (!line || (line[0] != 'F' && line[0] != 'C') || line[1] != ESPACO)
		return (ft_putendl_fd("Erro: identificador de cor inválido", 2), 0);

	id = line[0];

	// 2. validar caracteres + contar vírgulas
	int i = 2;
	int comma = 0;

	while (line[i])
	{
		if (!(ft_isdigit(line[i]) || line[i] == ESPACO || line[i] == COMMA || line[i] == NEWLINE))
			return (ft_putendl_fd("Erro: caracteres inválidos na cor", 2), 0);
		if (line[i] == ',')
			comma++;
		i++;
	}

	if (comma != 2)
		return (ft_putendl_fd("Erro: número inválido de vírgulas", 2), 0);

	// 3. split
	rgb = ft_split(line + 2, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (ft_putendl_fd("Erro: formato RGB inválido", 2), 0);

	// 4. validar números
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_putendl_fd("Erro: RGB fora do intervalo (0-255)", 2), 0);

	// 5. evitar duplicação
	if (id == 'F')
	{
		if (game->f_set)
			return (ft_putendl_fd("Erro: F já definido", 2), 0);
		game->floor_color = (r << 16) | (g << 8) | b;
		game->f_set = 1;
	}
	else
	{
		if (game->c_set)
			return (ft_putendl_fd("Erro: C já definido", 2), 0);
		game->ceiling_color = (r << 16) | (g << 8) | b;
		game->c_set = 1;
	}
	free_split(rgb);
	return (1);
}