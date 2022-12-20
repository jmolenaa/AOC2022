/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 16:31:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/12/06 08:43:35 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_strlst
{
	char			*str;
	struct s_strlst	*next;
}					t_strlst;

char		*get_next_line(int fd);
int			strlenornewline(char *str, int newlineornot);
char		*substr(char *str, int start, int newlineornot, int freecheck);
t_strlst	*freeing(t_strlst *strlist, char **strtemp);
int			stringcpy(char *dest, char *src, int size);

#endif