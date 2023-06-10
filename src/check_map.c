/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:03:01 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/10 19:21:12 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	return_true_count_up(size_t *orientation)
{
	*orientation += 1;
	return (true);
}

static bool	is_valid_characters(const char c, size_t *orientation)
{
	if (c == ' ')
		return (true);
	else if (c == '0')
		return (true);
	else if (c == '1')
		return (true);
	else if (c == 'N')
		return (return_true_count_up(orientation));
	else if (c == 'S')
		return (return_true_count_up(orientation));
	else if (c == 'E')
		return (return_true_count_up(orientation));
	else if (c == 'W')
		return (return_true_count_up(orientation));
	return (false);
}

static void	check_map_characters(t_map_node *map)
{
	size_t	i;
	size_t	orientation;

	orientation = 0;
	while (map)
	{
		i = 0;
		while (map->line[i])
		{
			if (!is_valid_characters(map->line[i], &orientation))
			{
				exit_error(
					"Unexpected characters are coming in the map.\n", false);
			}
			i++;
		}
		map = map->next;
	}
	if (orientation != 1)
		exit_error("Orientation must be one.\n", false);
}

void	check_map(t_map_node *map)
{
	check_map_characters(map);
}
