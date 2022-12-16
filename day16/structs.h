#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct s_valve
{
	char	*valvename;
	int		flowrate;
	char	**neigbors;
	struct s_valve	*next;
}			t_valve;

typedef struct s_visited
{
	char				*valvename;
	struct s_visited	*next;
}			t_visited;

typedef	struct s_route
{
	char			*valvevisited;
	struct s_route	*next;
	int				steps;
}					t_route;

t_valve	*get_valve_list(void);
void	printvalves(t_valve *firstvalve);
void	do_somthing(t_valve *first_valve,  t_valve *current, int remaining_steps, int *maxpressure, t_visited *list_visited, int pressure);

#endif