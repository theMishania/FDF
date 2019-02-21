/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:36:18 by chorange          #+#    #+#             */
/*   Updated: 2019/02/21 18:40:16 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_all(t_map *map_struct)
{
	int	i;

	i = 0;
	if (map_struct->map)
	{
		while (i < map_struct->n)
		{
			if (map_struct->map[i])
				free(map_struct->map[i]);
			i++;
		}
		free(map_struct->map);
	}
}
