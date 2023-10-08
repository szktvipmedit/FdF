#include "fdf.h"

// void z_values_conf(size_t fdfheight, size_t fdfwidth, int **z_values)
// {
// 	size_t height = 0;
// 	size_t width = 0;
// 	while(height < fdfheight)
// 	{
// 		width = 0;
// 		while(width < fdfheight)
// 		{
// 			printf("% i ", z_values[height][width]);
// 			width++;
// 		}
// 		printf("\n");
// 		height++;
// 	}
// }

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

int	deal_key(int key, t_fdf *fdf_info)
{
	if (fdf_info == NULL)
		return (0);
	//printf("%d\n", key);
	if (key == PLUS && fdf_info->zoom < 1000)
		fdf_info->zoom += 10;
	if (key == MINUS && fdf_info->zoom > 10)
		fdf_info->zoom -= 10;
	if (key == ALLOW_TOP)
		fdf_info->shift_y -= 10;
	if (key == ALLOW_RIGHT)
		fdf_info->shift_x += 10;
	if (key == ALLOW_BOTTOM)
		fdf_info->shift_y += 10;
	if (key == ALLOW_LEFT)
		fdf_info->shift_x -= 10;
	mlx_clear_window(fdf_info->mlx_ptr, fdf_info->win_ptr);
	fdf_info->img_ptr = mlx_new_image(fdf_info->mlx_ptr, WIDTH, HEIGHT);
	fdf_info->data_addr = mlx_get_data_addr(fdf_info->img_ptr,
											&fdf_info->bit_per_pixel,
											&fdf_info->size_line,
											&fdf_info->endian);
	draw(fdf_info);
	return (0);
}

int	close_window(t_fdf *fdf_info)
{
	mlx_destroy_window(fdf_info->mlx_ptr, fdf_info->win_ptr);
	exit(SUCCESS_EXIT);
	return (0);
}

void	error_handler(char *filename)
{
	if (ft_strlen(filename) == 0)
	{
		write(2, NON_FILENAME_ARGUMENT, NON_FILENAME_ARGUMENT_CC);
		exit(BAD_EXIT);
	}
	if (!ft_isverify_file_extension(filename, ".fdf"))
	{
		write(2, NOT_FDF_FILE, NOT_FDF_FILE_CC);
		exit(BAD_EXIT);
	}
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q fdf");
// }

int	main(int argc, char **argv)
{
	t_fdf	*fdf_info;

	if (argc == 2)
	{
		fdf_info = (t_fdf *)malloc(sizeof(t_fdf));
		error_handler(argv[1]);
		read_fdf(&fdf_info, argv[1]);
		fdf_info->zoom = 30;
		fdf_info->shift_x = 300;
		fdf_info->shift_y = 150;
		fdf_info->mlx_ptr = mlx_init();
		fdf_info->win_ptr = mlx_new_window(fdf_info->mlx_ptr, WIDTH, HEIGHT,
				"FDF");
		fdf_info->img_ptr = mlx_new_image(fdf_info->mlx_ptr, WIDTH, HEIGHT);
		fdf_info->data_addr = mlx_get_data_addr(fdf_info->img_ptr,
												&fdf_info->bit_per_pixel,
												&fdf_info->size_line,
												&fdf_info->endian);
		draw(fdf_info);
		mlx_key_hook(fdf_info->win_ptr, deal_key, fdf_info);
		mlx_hook(fdf_info->win_ptr, 17, 1L << 17, close_window, fdf_info);
		mlx_loop(fdf_info->mlx_ptr);
	}
	else
	{
		write(2, NON_FILENAME_ARGUMENT, NON_FILENAME_ARGUMENT_CC);
		exit(BAD_EXIT);
	}
}
