#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"

/*	This function gets the line in the file where the
	corresponding directory starts	*/
void	getdir(char *str, int fd)
{
	char	dirname[20];
	int		n;
	int		check = 0;

	/* Making string with directory name*/
	sscanf(str, "dir %s", dirname);
	n = ft_strlen(dirname);
	*(dirname + n) = '\n';
	*(dirname + n + 1) = '\0';
	while (1)
	{
		str = get_next_line(fd);
		if (*str == 'd')
		{
			/*	This checks if we have another dir with
				the same namesomewhere between the
				our dir and the contents of that dir*/
			if (ft_strncmp(str + 4, dirname, n) == 0)
				check = 1;
		}
		if (*(str + 2) == 'c')
		{
			/*	This checks if we are at the cd dirname
				in the file which is where the contents
				of our dir are shown, if we had another
				dir declaration before that we skip over
				this instance*/
			if (ft_strncmp(str + 5, dirname, n) == 0)
			{
				if (check)
					check = 0;
				else
					break ;
			}
		}
	}
	/*Skipping over "$ ls" command*/
	get_next_line(fd);
}

/*counts size of directory*/
int	sizedir(char *str, int fd, int *total)
{
	int		size;
	off_t	temp;

	getdir(str, fd);
	size = 0;
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
			size = size + ft_atoi(str);
	}
	if (size < 100000)
		*total = *total + size;
	return (size);
}

int	main()
{
	char *str;
	int	total;
	int fd = open("input", O_RDONLY);
	int	size;
	off_t temp;
	/*skips over first to lines*/
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
			/*	adds dir size to totalsize by calling
				recursively, stores where we are in 
				the file and later sets us back to that 
				point*/
			temp = lseek(fd, 0, SEEK_CUR);
			size = size + sizedir(str, fd, &total);
			lseek(fd, temp, SEEK_SET);
		}
		else
			/* adds filesize to totalsize*/
			size = size + ft_atoi(str);
	}
	/*adds to total if size smaller than 100000*/
	if (size < 100000)
		total = total + size;
	/* counts empty space for next part :)*/
	int emptyspace = 70000000 - size;
	printf("%d\n", emptyspace);
	printf("total : %d", total);
}