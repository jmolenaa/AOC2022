/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 16:31:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/12/14 11:35:27 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_strlst
{
	char			*str;
	struct s_strlst	*next;
}					t_strlst;

typedef struct s_grid
{
	char	**cave;
	int		minx;
	int		maxx;
	int		maxy;
}			t_grid;

char		*get_next_line(int fd);
int			strlenornewline(char *str, int newlineornot);
char		*substr(char *str, int start, int newlineornot, int freecheck);
t_strlst	*freeing(t_strlst *strlist, char **strtemp);
int			stringcpy(char *dest, char *src, int size);
t_grid		make_grid(void);


#endif