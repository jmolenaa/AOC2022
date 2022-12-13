#ifndef LIST_H
# define LIST_H

typedef struct s_signal
{
	char			*packet;
	struct s_signal *nextpacket;
}					t_signal;

#endif