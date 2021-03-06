/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 17:25:36 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/11 18:14:40 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define INIT_PROGNAME	extern const char *__progname
# define PROGNAME		__progname
# define BUFF_SIZE		32
# define RD_BUFFSIZE	1
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

/*
** flags:
**  #  | 1
**  0  | 2
**  -  | 4
** ' ' | 8
**  +  | 16
**  '  | 32
**  I  | 64
*/

typedef struct		s_pftype
{
	int				nb;
	int				zero;
	int				flags;
}					t_pftype;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_file
{
	char			*file_content;
	int				fd;
}					t_file;

int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_ishex(char c);
char				ft_hexval(char c);
unsigned int		ft_hextoi(char *str);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *s1, const void *s2, size_t n);
void				*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *s1, const void *s2, size_t n);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_newstrcat(char *dest, const char *src);
char				*ft_strncpy(char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
								size_t len);
size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **ap);
void				ft_strclr(char *s);
void				ft_strnclr(char *s, int nb);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putfloat_fd(float n, int precision, int fd);
int					ft_error(char const *s);
int					get_next_line(int const fd, char **line);
int					ft_printf(const char *format, ...);
void				ft_puthex(unsigned int n);
char				*ft_hextoa(unsigned int n);
char				*ft_readfile(int fd);
char				*ft_getfile(char *name);
char				*ft_strdup_trim(char *str);
size_t				ft_strlen_trim(char *str);
size_t				ft_strlen_trim2(char *str);
char				*ft_strndup(char *str, size_t len);
int					ft_abs(int nb);
void				ft_putfloat(float nb);
float				ft_atof(char *str);
char				*ft_strcchr(const char *s, int c, int f);
char				*ft_concat(char *s1, char *s2);
void				ft_lstadd(t_list **alst, t_list *nw);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void *content);
char				*ft_ftoa(float nb, int precision);
unsigned int		limit_nb(unsigned int nb, unsigned int max);

#endif
