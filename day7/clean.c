#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

int	sizedir(char *str, int fd, int *total)
{
	int		size;
	int		file;
	char	dirname[20];
	int		n;
	char	*dirline;
	char	*cddirline;
	off_t	temp;
	int		check = 0;

	sscanf(str, "dir %s", dirname);
	n = ft_strlen(dirname);
	*(dirname + n) = '\n';
	*(dirname + n + 1) = '\0';
	dirline = ft_strjoin("dir ", dirname);
	cddirline = ft_strjoin("$ cd ", dirname);
	size = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (*str == 'd')
		{
			if (ft_strncmp(str, dirline, 20) == 0)
				check = 1;
		}
		if (*(str + 2) == 'c')
		{
			if (ft_strncmp(str, cddirline, 20) == 0)
			{
				if (check)
					check = 0;
				else
					break ;
			}
		}
	}
	get_next_line(fd);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL || *str == '$')
			break ;
		if (*str == 'd')
		{
			temp = lseek(fd, 0, SEEK_CUR);
			size = size + sizedir(str, fd, total);
			lseek(fd, temp, SEEK_SET);
		}
		else
		{
			sscanf(str, "%d ", &file);
			size = size + file;
		}
	}
	if (size < 100000)
		*total = *total + size;
	*(dirname + n) = '\0';
	// printf("dir : %s has %d bytes\n", dirname, size);
	return (size);
}

int	main()
{
	char *str;
	int	total;
	int fd = open("input", O_RDONLY);
	int	size;
	int	file;
	off_t temp;
	get_next_line(fd);
	get_next_line(fd);
	size = 0;
	total = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (*str == '$')
			break ;
		if (*str == 'd')
		{
			temp = lseek(fd, 0, SEEK_CUR);
			size = size + sizedir(str, fd, &total);
			lseek(fd, temp, SEEK_SET);
		}
		else
		{
			sscanf(str, "%d ", &file);
			size = size + file;
		}
	}
	if (size < 100000)
		total = total + size;
	int emptyspace = 70000000 - size;
	printf("%d\n", emptyspace);
	// printf("dir : \\ has %d bytes\n", size);
	printf("total : %d", total);
}