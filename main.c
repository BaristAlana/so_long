#include <stdlib.h>
#include "MLX42.h"

int main(void)
{
    mlx_t	*mlx_ptr;

    mlx_ptr = mlx_init(25, 25, "test", 0);
    mlx_terminate(mlx_ptr);
    //free(mlx_ptr);
	exit(0);
}
