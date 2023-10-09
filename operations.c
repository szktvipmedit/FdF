/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:15:40 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/09 17:20:56 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	shift_map(t_fdf *fdf_info, int key)
{
	if (key == ALLOW_TOP)
		fdf_info->shift_y -= 10;
	if (key == ALLOW_RIGHT)
		fdf_info->shift_x += 10;
	if (key == ALLOW_BOTTOM)
		fdf_info->shift_y += 10;
	if (key == ALLOW_LEFT)
		fdf_info->shift_x -= 10;
}

void	zoom_map(t_fdf *fdf_info, int key)
{
	if (key == PLUS && fdf_info->zoom < 1000)
		fdf_info->zoom += 10;
	if (key == MINUS && fdf_info->zoom > 10)
		fdf_info->zoom -= 10;
}