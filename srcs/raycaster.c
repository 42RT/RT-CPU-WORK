/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 14:22:46 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/17 16:36:36 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_color	init_color_black(void)
{
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	return (color);
}

t_ray	init_ray(t_env *env)
{
	t_ray	ray;
	double	x;
	double	y;
	double	z;

	x = VPUL.x + env->VDYX * env->y * YINDENT -
		env->VDXX * env->x * XINDENT - CAMPOSX;
	y = VPUL.y + env->VDYY * env->y * YINDENT -
		env->VDXY * env->x * XINDENT - CAMPOSY;
	z = VPUL.z + env->VDYZ * env->y * YINDENT -
		env->VDXZ * env->x * XINDENT - CAMPOSZ;
	ray.pos = CAMPOS;
	ray.vecdir.x = x / sqrt(x * x + y * y + z * z);
	ray.vecdir.y = y / sqrt(x * x + y * y + z * z);
	ray.vecdir.z = z / sqrt(x * x + y * y + z * z);
	ray.dist = 1000000;
	ray.color = init_color_black();
	return (ray);
}

void	raycaster(t_env *env)
{

	t_ray	*ray;
	t_color	color;
	int		cnt;
	int		bar;
	int		percent;

	printf("RT : \033[33mSTART CALCULATING THE SCENE : \033[0m");
	ray = (t_ray*)malloc(sizeof(t_ray));
	color = init_color_black();
	env->y = 0;
	env->x = 0;
	percent = 2;
	cnt = 0;
	bar = 0;
	printf("\033[33m%d PIXEL ...\033[0m\n", env->set->height * env->set->width);
	printf("([");
	while (env->x < env->set->height)
	{
		while (env->y < env->set->width)
		{
			*ray = init_ray(env);
			color = trace(env, ray, 0);
			pixel_put(env, color);
			++env->y;
			cnt++;
			if (cnt % (env->set->height * env->set->width * percent / 100) == 0)
			{
				bar++;
				printf("\033[1;32m=\033[0m");
			}
		}
		env->y = 0;
		++env->x;
	}
	printf("])\n");
	printf("RT : \033[33mApplying Render ... \033[0m: ");
	SDL_RenderPresent(env->img);
	printf("\033[1;32mDISPLAYED\033[0m\n");
	free(ray);
}
