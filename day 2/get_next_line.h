/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 16:31:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2022/11/27 13:20:14 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
int		strlenornewline(char *str, int newlineornot);
char	*substr(char *str, int start, int newlineornot, int freecheck);
t_list	*freeing(t_list *strlist, char **strtemp);
int		stringcpy(char *dest, char *src, int size);

#endif