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

int	sizedir(char *str, int fd, int neededspace, int *spacetoremove)
{
	int		size;
	off_t	temp;

	size = 0;
	getdir(str, fd);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL || *str == '$')
			break ;
		if (*str == 'd')
		{
			temp = lseek(fd, 0, SEEK_CUR);
			size = size + sizedir(str, fd, neededspace, spacetoremove);
			lseek(fd, temp, SEEK_SET);
		}
		else
			size = size + ft_atoi(str);
	}
	/*	changes what size we're removing depending
		on counted size*/
	if (size > neededspace && size < *spacetoremove)
		*spacetoremove = size;
	return (size);
}

int	main()
{
	char *str;
	int fd = open("input", O_RDONLY);
	int	size;
	int	neededspace = 30000000 - 24650017;
	printf("%d\n", neededspace);
	int	spacetoremove = 45349983;
	off_t temp;
	get_next_line(fd);
	get_next_line(fd);
	size = 0;
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
			size = size + sizedir(str, fd, neededspace, &spacetoremove);
			lseek(fd, temp, SEEK_SET);
		}
		else
			/* adds filesize to totalsize*/
			size = size + ft_atoi(str);
	}
	printf("%d\n", spacetoremove);
}