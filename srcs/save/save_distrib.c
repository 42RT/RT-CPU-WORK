#include <fcntl.h>
#include <raytracer.h>
#include <parser.h>

void	save_dis_nbr(float obj, char *str, int fd, int tab)
{
	write_padding(fd, tab);
	ft_putstr_fd("\"", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\": ", fd);
	ft_putnbr_fd(obj, fd);
	ft_putstr_fd(",\n", fd);
}

void	save_dis_str(char *str, char *name, int fd, int tab)
{
	write_padding(fd, tab);
	ft_putstr_fd("\"", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\": ", fd);
	ft_putstr_fd(name, fd);
	ft_putstr_fd(",\n", fd);
}

void	save_dis_triple(t_vector obj, char *str, int fd, int tab)
{
	write_padding(fd, tab);
	ft_putstr_fd("\"", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\": {\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"x\": ", fd);
	ft_putnbr_fd(obj.x, fd);
	ft_putstr_fd(",\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"y\": ", fd);
	ft_putnbr_fd(obj.y, fd);
	ft_putstr_fd(",\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"z\": ", fd);
	ft_putnbr_fd(obj.z, fd);
	ft_putchar_fd('\n', fd);
	write_padding(fd, tab);
	ft_putstr_fd("},", fd);
	ft_putchar_fd('\n', fd);
}

void	save_dis_angle(t_vector obj, int fd, int tab)
{
	write_padding(fd, tab);
	ft_putstr_fd("\"angle\": {\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"x\": ", fd);
	ft_putnbr_fd((obj.x * 90 / M_PI_2), fd);
	ft_putstr_fd(",\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"y\": ", fd);
	ft_putnbr_fd((obj.y * 90 / M_PI_2), fd);
	ft_putstr_fd(",\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"z\": ", fd);
	ft_putnbr_fd((obj.z * 90 / M_PI_2), fd);
	ft_putchar_fd('\n', fd);
	write_padding(fd, tab);
	ft_putstr_fd("},", fd);
	ft_putchar_fd('\n', fd);
}

void	save_dis_cap(int cap1, int cap2, int fd, int tab)
{
	write_padding(fd, tab);
	ft_putstr_fd("\"cap\": {\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"cap1\": ", fd);
	ft_putnbr_fd(cap1, fd);
	ft_putstr_fd(",\n", fd);
	write_padding(fd, tab + 1);
	ft_putstr_fd("\"cap2\": ", fd);
	ft_putnbr_fd(cap2, fd);
	ft_putchar_fd('\n', fd);
	write_padding(fd, tab);
	ft_putstr_fd("},", fd);
	ft_putchar_fd('\n', fd);
}
