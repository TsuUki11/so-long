#include <mlx.h>
#include <stdio.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int	x = 100;
	int y = 100;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 400, 400, "Hello world!");
	img.img = mlx_new_image(mlx, 400, 400);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	while (y <= 300)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		x++;
		if (x == 300)
		{
			y++;
			x = 100;
		}
	}
	x = 0;
	y = 0;
	while (y <= 400)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FFFFFF);
		x++;
		if (x == 400)
		{
			y++;
			x = 0;
		}
		if (y >= 100 && y <= 300)
		{
			if (x == 100)
				x = 300;
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}