/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/08/21 22:56:18 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/16 18:03:19 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# ifdef __APPLE__
#  include <SDL.h>
#  include <SDL_ttf.h>
# else
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_ttf.h>
# endif

# include <hdr_colors.h>

# define HOOK_KEY		1
# define HOOK_MOUSE		2
# define HOOK_EXPOSE	3
# define SINGLE_BUFFER	0
# define DOUBLE_BUFFER	1

typedef struct		s_img
{
	int				width;
	int				height;
	t_color			*data;
	void			*mlx;
}					t_img;

typedef struct		s_gfx
{
	SDL_Event		event;
	char			*title;
	void			*win;
	unsigned int	win_id;
	void			*renderer;
	void			*texture;
	int				act;
	t_img			*buff[8];
	int				expose;
}					t_gfx;

/*
** init GFX before using it
*/
t_gfx				*gfx_init(char *title, int res_x, int res_y,
									int buff_nb);
void				gfx_exit(t_gfx *gfx, int ex);
/*
** reload main window, and reset it if size changed
*/
t_gfx				*gfx_reload(t_gfx *gfx, int res_x, int res_y,
									int buff_nb);

/*
** image creation and manipulation
*/
t_img				*gfx_new_image(t_gfx *gfx, int res_x, int res_y);
void				gfx_destroy_image(t_img *img);
void				gfx_pixel_put_to_image(t_img *img, int x, int y,
												t_color color);
t_color				gfx_get_pixel_color(t_img *img, int x, int y);
void				gfx_blitz_image(t_gfx *gfx, int x, int y, t_img *img);
void				gfx_display_image(t_gfx *gfx, int x, int y, t_img *img);
void				gfx_blitz_black_image(t_gfx *gfx, int x, int y);
void				gfx_fill_image(t_img *img, unsigned int width,
									unsigned int height, t_color color);

/*
** several utilities
*/
int					gfx_loop(t_gfx *gfx);
int					gfx_poll(t_gfx *gfx);
void				gfx_pixel_put(t_gfx *gfx, int x, int y,
										t_color color);
void				gfx_exit(t_gfx *gfx, int exit);
void				gfx_flip_screen(t_gfx *gfx);
unsigned int		get_alpha_color(unsigned int origin, unsigned int color);

/*
** change virtual screen (1-4)
*/
void				gfx_change_screen(t_gfx *gfx, unsigned int nb);

#endif
