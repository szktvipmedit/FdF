/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:30:45 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/09 17:02:18 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_fdf(t_fdf **fdf_info, char *filename)
{
	(*fdf_info)->height = get_fdfheight(filename);
	(*fdf_info)->width = get_fdfwidth(filename);
	printf("height = %zu\n", (*fdf_info)->height);
	printf("width = %zu\n", (*fdf_info)->width);
	(*fdf_info)->z_values = malloc(sizeof(int *) * (*fdf_info)->height);
	(*fdf_info)->z_values = get_fdfmap((*fdf_info)->z_values, filename,
			(*fdf_info)->width, (*fdf_info)->height);
}

size_t	get_fdfheight(char *filename)
{
	int		fd;
	size_t	height;
	char	*line;

	height = 0;
	fd = open(filename, O_RDONLY);
	error_fd(fd);
	line = get_next_line(fd);
	if (line)
		height++;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		height++;
	}
	close(fd);
	return (height - 1);
}

size_t	get_fdfwidth(char *filename)
{
	int		fd;
	size_t	width;
	char	*line;
	char	**row_values;
	size_t	i;

	width = 0;
	fd = open(filename, O_RDONLY);
	error_fd(fd);
	line = get_next_line(fd);
	row_values = ft_split(line, ' ');
	free(line);
	while (row_values[width])
		width++;
	ft_split_memory_cleaner(width, row_values);
	return (width);
}

void	get_fdfmap_generate_array(int fd, int **z_values, size_t width,
		size_t height)
{
	size_t	i;
	size_t	j;
	char	**sp_row;
	int		*row_values;
	char	*row;

	j = 0;
	i = 0;
	while (j < height)
	{
		i = 0;
		row = get_next_line(fd);
		sp_row = ft_split(row, ' ');
		free(row);
		row_values = malloc(sizeof(int) * width);
		while (sp_row[i] && i < width)
		{
			row_values[i] = ft_atoi(sp_row[i]);
			i++;
		}
		error_fdf_format(i, width);
		ft_split_memory_cleaner(width, sp_row);
		z_values[j] = row_values;
		j++;
	}
}

int	**get_fdfmap(int **z_values, char *filename, size_t width, size_t height)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	error_fd(fd);
	get_fdfmap_generate_array(fd, z_values, width, height);
	return (z_values);
}