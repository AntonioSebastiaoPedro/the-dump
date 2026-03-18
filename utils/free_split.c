/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-18 14:30:22 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-18 14:30:22 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 # include "../includes/cub.h"

 void   free_split(char **arr)
 {
    int i;
    if (!arr)
        return ;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
 }