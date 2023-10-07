#include "fdf.h"
size_t get_fdfheight(char *filename)
{
	int fd;
	size_t height;
	char *line;
	height = 0;
	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		write(2, COULD_NOT_OPEN_FILE, COULD_NOT_OPEN_FILE_CC);
		exit(BAD_EXIT);
	}
	else
	{
		line = get_next_line(fd);
		if(line)
			height++;
		while(line)
		{
			free(line);
			line = get_next_line(fd);
			height++;
		}
	}
	close(fd);
	return height - 1;
}

void	split_free(char **str, size_t sec)
{
	while (str[sec])
	{
		free(str[sec]);
		sec--;
	}
	free(str);
}

size_t get_fdfwidth(char *filename)
{
	int fd;
	size_t width;
	char *line;
	char **row_values;
	size_t i;
	
	width = 0;
	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		write(2, COULD_NOT_OPEN_FILE, COULD_NOT_OPEN_FILE_CC);
		exit(BAD_EXIT);
	}
	else
	{
		line = get_next_line(fd);
		row_values = ft_split(line, ' ');
		while(row_values[width])
			width++;
	}
	i = width;
	
	//free(line);
	//split_free(row_values, width-1);
	//while(row_values[--i] && i >= 0)
	 	//free(row_values[i]);
	 //free(row_values);
	return width;
}

int **get_fdfmap(int **z_values, char *filename, size_t width, size_t height)
{
	int fd;
	char **sp_row;
	int *row_values;
	size_t i;
	size_t j;
	char *row;
	j = 0;	
	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		write(2, COULD_NOT_OPEN_FILE, COULD_NOT_OPEN_FILE_CC);
		exit(BAD_EXIT);
	}
	while(j < height)
	{
		i = 0;
		row = get_next_line(fd);\
		sp_row = ft_split(row, ' ');
		free(row);
		row_values = malloc(sizeof(int) * width);
		while(i < width)
		{
			row_values[i] = ft_atoi(sp_row[i]);
			i++;
		}
		z_values[j] = row_values;

		j++;
	}
	
	// while(sp_row[--width])
	// 	free(sp_row[width]);
	// free(sp_row);
	return z_values;
}