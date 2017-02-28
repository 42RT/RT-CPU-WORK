/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 17:59:48 by rmorel            #+#    #+#             */
/*   Updated: 2014/12/16 17:59:50 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <unistd.h>
# include <fcntl.h>
# include <libxmlx.h>

void	save_image(void *img, char *name, t_img *param);

#endif
