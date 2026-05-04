/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:22:44 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 10:33:09 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static int	is_ignored(char *name)
{
	return (!strcmp(name, "minilibx-linux")
		|| !strcmp(name, "bass"));
}

static int	is_source_file(char *name)
{
	char	*ext;

	ext = strrchr(name, '.');
	if (!ext)
		return (0);
	return (!strcmp(ext, ".c") || !strcmp(ext, ".h"));
}

static void	run_norminette(char *path)
{
	char	cmd[1024];

	snprintf(cmd, sizeof(cmd), "norminette \"%s\"", path);
	system(cmd);
}

static void	scan_dir(char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	char			full_path[1024];

	dir = opendir(path);
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (strcmp(entry->d_name, ".")
			&& strcmp(entry->d_name, ".."))
		{
			snprintf(full_path, sizeof(full_path), "%s/%s", path,
				entry->d_name);
			if (entry->d_type == DT_DIR
				&& !is_ignored(entry->d_name))
				scan_dir(full_path);
			else if (entry->d_type == DT_REG
				&& is_source_file(entry->d_name))
				run_norminette(full_path);
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

int	main(void)
{
	scan_dir(".");
	return (0);
}
